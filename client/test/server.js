var net = require('net');
var clientList = [];
var chatServer = net.createServer();

chatServer.on('connection', function(client){
  console.log('Server connected!');
  client.name = client.remoteAddress + ':' + client.remotePort;
  console.log(client.name);

  clientList.push(client);
  client.on('data', function(data){
    broadcast(data.toString(), client);
  });

  client.on('end', function(){
    removeClient(client);
    console.log('client:' + client.name + ' disconnected!');
  });

  function broadcast(msg, client){
    for (var i = 0; i < clientList.length; ++i)
    {
      if( client != clientList[i] ){
        clientList[i].write(client.name + 'says ' + msg);
      }

    }
  };

  function removeClient(client){
    for (var i = 0; i < clientList.length; ++i)
    {
      if( client == clientList[i] ){
        clientList.splice(i, 1);
        break;
      }
    }
  };


});

chatServer.listen(8787);