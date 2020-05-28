const uint ServerPort = 7755;
WiFiServer Server(ServerPort);
WiFiClient RemoteClient;

void ServerStart() {
    Server.Begin()
}

void CheckForConnections()
{
  if (Server.hasClient())
  {
    // If we are already connected to another computer, 
    // then reject the new connection. Otherwise accept
    // the connection. 
    if (RemoteClient.connected())
    {
      Serial.println("Connection rejected");
      Server.available().stop();
    }
    else
    {
      Serial.println("Connection accepted");
      RemoteClient = Server.available();
    }
  }
}

void UDPConnect()
{
    String mocapServer = ReadStringEEPROM(3);
    String mocapServerPort = ReadStringEEPROM(4);

    IPAddress ipAddress = IPAddress();
    ipAddress.fromString(mocapServer);

    int port = mocapServerPort.toInt();
    
    udpClient.connect(ipAddress, port);   
}

void UDPSendData(String message)
{
    String mocapServerPort = ReadStringEEPROM(4);
    int port = mocapServerPort.toInt();

    char charBuffer[1024];
    message.toCharArray(charBuffer, 1024);

    if (udpClient.connected())
        udpClient.broadcastTo(charBuffer, port);
    else
        UDPConnect();
}
