import socket
import time
import threading
import Functions

HEADER=35
IP="192.168.100.7"
PORT=5050
FORMAT="utf-8"
DISCONNECT_MESSAGE="!DISCONNECT"
id=0
F_ADDR=(IP,PORT)

server= socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(F_ADDR)

#server communication protocol is as followed:
#client should send in header information about
#the data that shall be recieved, such as following:
#NameOfTheFunc_SizeOfTheData

#For example:  func1_40
#that means that message is 40 bytes long and shall be interpreted as func1_
#and after many blank spaces to fill the remaining characters in the header
#comes the right message, which contains the object written in string in binary,
#every attribute of object is separated by |
#and every object is separated by &
def code_message(message,f_header):
    message=message.encode(FORMAT)
    m_len=len(message)
    m_header = f_header+str(m_len)
    m_header= m_header.encode(FORMAT)
    #padding header
    m_header+=b' '*(HEADER-len(m_header))
    message=m_header+message
    return message
#single message is sent in single connection, after sending back connection is closed
def handle_client(connection,address):
    print(f"\nNEW CONNECTION: address:{address}")
    msg_length=connection.recv(HEADER).decode(FORMAT)
    if msg_length:
        t=msg_length.split("_")
        t[0]+="_"
        func=t[0]
        msg_length=int(t[1])
        msg=connection.recv(msg_length).decode(FORMAT)
        msg=msg[:len(msg)-1]
        s="default_msg"
        match func:
            case "getID_":
                s=Functions.getID()
            case "changeActiveUserState_":
                s = Functions.changeActiveUserState(msg)
            case "retrieveActiveUsers_":
                s =Functions.retrieveActiveUsers()
            case "registeruser_":
                s=Functions.registerUser(msg)
            case "registerScreeningRoom_":
                s=Functions.registerScreeningRoom(msg)
            case "registerMovie_":
                s = Functions.registerMovie(msg)
            case "endMovie_":
                s= Functions.endMovie(msg)
            case "deleteActiveMovie_":
                s=Functions.deleteMovie(msg,"")
            case "deleteInActiveMovie_":
                s = Functions.deleteMovie(msg, "In")
            case "unregisterClient_":
                s = Functions.unregisterClient(msg)
            case "retrieveMovies_":
                s = Functions.retrieveMovies()
            case "retrieveScreeningRooms_":
                s = Functions.retrieveScreeningRooms()
            case "clientLogin_":
                s=Functions.clientLogin(msg)
            case "checkLoginAndMail_":
                s = Functions.checkLoginAndEmail(msg)
            case "adminLogin_":
                s=Functions.canAdminLog(msg)
            case "deleteRoom_":
                s = Functions.deleteRoom(msg)
            case "getUsersVulnerableData_":
                s = Functions.getUsersVulnerableData(msg)
            case "getIdByLogin_":
                s = Functions.getIdByLogin(msg)
            case "updateScreeningRoom_":
                s = Functions.updateScreeningRoom(msg)
            case "retrieveUserByID_":
                s = Functions.retrieveUserByID(msg)
            case "retrieveScreeningRoomByID_":
                s = Functions.retrieveScreeningRoomByID(msg)
            case "retrieveMovieByID_":
                s = Functions.retrieveMovieByID(msg)
            case "getUsersIDs_":
                s = Functions.getUsersIDs(msg)
            case "getMoviesIDs_":
                s = Functions.getMoviesIDs(msg)
            case "getScreeningRoomsIDs_":
                s = Functions.getScreeningRoomsIDs(msg)
            case _:
                pass
        message_to_send = code_message(s, t[0])
        connection.send(message_to_send)
    print(f"[{address}] Func name: [{t[0]}]   Message:[{msg}] Message_sent_back[{s}]")
    connection.close()

def start():
    server.listen()
    print(f"Server is listening on {IP} port {PORT}")
    while True:
        connection, address=server.accept()
        thread = threading.Thread(target=handle_client, args=(connection,address))
        thread.start()
        print(f"ACTIVE CONNECTIONS: {threading.active_count()-1}\n")

print("STARTING SERVER")
start()