
#ifndef  SESSION_H
#define  SESSION_H

#include <boost/asio.hpp>

class Session
{
public:
    Session(boost::asio::io_service & ios, boost::asio::ip::tcp::socket & sock, const char * rip, const int rport);
    ~Session();

    void StartEcho();

protected:

    virtual void Write(const boost::system::error_code & error);

    virtual void Read(const boost::system::error_code & error, size_t bytes_transferred);

private:
    boost::asio::io_service & m_ios;
    boost::asio::ip::tcp::socket & m_sock;
    const char * m_rip;
    const int m_rport;
    char * m_write_buf;
    size_t m_write_buf_len;
    char * m_read_buf;
    size_t m_read_buf_len;
};


#endif   /* SESSION_H */
