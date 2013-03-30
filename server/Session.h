
#ifndef  SESSION_H
#define  SESSION_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace imsvr{
namespace server{

class Session // : public boost::enable_shared_from_this<Session>
{
public:
    typedef boost::shared_ptr<Session> PtrType;
    typedef std::string IDType;

    Session(boost::asio::io_service & ios);
    ~Session();

    const IDType GetID(){ return m_id;}
    void SetID(IDType & id) {if(m_id != id) m_id = id;}
    
    boost::asio::io_service & ios() {return m_ios;} 
//     void ios(boost::asio::io_service & ios){m_ios = ios;}

    boost::asio::ip::tcp::socket & socket(){ return m_sock;}

    void Run();

    void Send(const char * buf, size_t sz);

protected:
    static const int MAX_BUF_SZ = 9999+4;

    void HandleRead(const boost::system::error_code & error, const std::size_t & bytes_transferred);
    void HandleWrite(const boost::system::error_code & error);

private:
    IDType m_id;
    boost::asio::io_service & m_ios;
    boost::asio::ip::tcp::socket m_sock;
    char * m_read_buf;
    char * m_write_buf;

    static int id;
};

} /*  namespace server */
} /*  namespace imsvr */

#endif   /* SESSION_H */
