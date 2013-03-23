
#ifndef  SERVER_H
#define  SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <cstring>

//#include <boost/enable_shared_from_this.hpp>
//class Session : public boost::enable_shared_from_this<Session>
class Session
{
public:
    Session(boost::asio::io_service & ios)
    :m_ios(ios), m_sock(ios), m_msg(new char[MAX_BUF_SZ]), m_write_msg(new char[MAX_BUF_SZ])
    {
        memset(m_msg, 0, sizeof(m_msg));
    }
    ~Session()
    {
        std::cout << "Seesion Free" << std::endl;
        delete m_write_msg; m_write_msg = NULL;
        delete m_msg;       m_msg = NULL;
    }
    
    void Run()
    {
        //register write & read handle  TODO
        boost::asio::async_read(m_sock, 
            boost::asio::buffer(m_msg, sizeof(m_msg)),
            boost::asio::transfer_at_least(1),
            boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void Send(const char * buf, size_t sz)
    {
        assert(buf);
        sz = sz > MAX_BUF_SZ ? MAX_BUF_SZ : sz;
        memcpy(m_write_msg, buf,  sz);

        boost::asio::async_write(m_sock,
                boost::asio::buffer(m_write_msg, sz),
                boost::bind(&Session::handle_write, this,
                    boost::asio::placeholders::error));
    }
    boost::asio::ip::tcp::socket & socket()
    {
        return m_sock;
    }
protected:
    void handle_read(const boost::system::error_code & error
        , const std::size_t & bytes_transferred)
    {
        if(!error && bytes_transferred > 0)
        {
            std::cout << m_msg << std::endl;
            this->Send(m_msg, bytes_transferred); 

            memset(m_msg, 0, sizeof(m_msg));
            boost::asio::async_read(m_sock, 
                boost::asio::buffer(m_msg, sizeof(m_msg)),
                boost::asio::transfer_at_least(1),
                boost::bind(&Session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            std::cout << "got en error :" << error << std::endl;
            // free myself TODO?????
        }
    }
    void handle_write(const boost::system::error_code & error)
    {
        if(!error)
        {
            std::cout << "write OK !" << std::endl; 
        }
        else
        {
            std::cout << "write got an error :" << error << std::endl;
        }
    }
private:
    boost::asio::io_service & m_ios;
    boost::asio::ip::tcp::socket m_sock;
    static const int MAX_BUF_SZ = 1024;
    char * m_msg;
    char * m_write_msg;
};
class Server    
{
public:
    Server(boost::asio::io_service & ios, const int port)
    :m_ios(ios), m_acceptor(ios, 
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
    }
    ~Server()
    {
    }

    void Run()
    {
        std::cout << "already has client : " << m_sessions.size() << std::endl;
        boost::shared_ptr<Session> psess (new Session(m_ios));
        m_sessions.push_back(psess);
        m_acceptor.async_accept(psess->socket(), 
            boost::bind(&Server::handle_accept, this, psess, 
            boost::asio::placeholders::error));
    }
    void handle_accept(boost::shared_ptr<Session> psess, const boost::system::error_code  & error)
    {
        if(!error)
        {
            std::cout << "accept one client" << std::endl;
            psess->Run();
        }
        Run();
    }

private:
    boost::asio::io_service & m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::list<boost::shared_ptr<Session> > m_sessions;
};

#endif   /* SERVER_H */
