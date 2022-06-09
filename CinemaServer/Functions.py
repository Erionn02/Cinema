import sqlite3

#w dostępach do baz danych należałoby zastosować mechanizmy blokad wyłącznych i współdzielonych,
#należałoby również szyfrować wrażliwe dane oraz weryfikować przesyłaną przez użytkownika wiadomość
#pod kątem SQLInjecta etc...
#natomiast przez uproszczony model aplikacji oraz serwera postanowiłem ich nie realizować.

def getID():
    fr = open("ID_HOLDER.txt", "r")
    s = fr.read()
    fr.close()
    fw = open("ID_HOLDER.txt", "w")
    fw.write(str(int(s) + 1))
    fw.close()
    return s
def registerUser(info):
    t = info.split("|")
    login = t[0]
    password = t[1]
    email = t[2]
    name = t[3]
    lastName = t[4]
    birthday = t[5]
    id = t[6]
    balance = t[7]
    tickets = ""
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(
            f"INSERT INTO Active_users VALUES('{login}','{password}','{email}','{name}','{lastName}','{birthday}','{id}','{balance}','{tickets}')")
        db.commit()
        db.close()
        return "Successfully registered user."
    except Exception as e:
        db.close()
        return "Failed to register given user " + str(e)
def retrieveActiveUsers():
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users")
        list = cursor.fetchall()
        string = ""
        if len(list) > 0:
            for record in list:
                i=0
                for element in record:
                    if i<3:
                        i+=1
                        continue
                    string += element + "|"
                string = string[:len(string)-1]
                string += "&"
            string = string[:len(string) - 1]
        db.close()
        return string
    except Exception as e:
        db.close()
        return "Something went wrong: " + str(e)
def changeActiveUserState(info):
    t = info.split("|")
    id = t[3]
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE id = (?)",(id,))
        l=cursor.fetchall()
        client = l[0]
        client=list(client)
        info=info.split("|")
        cursor.execute(f"DELETE FROM Active_users WHERE id = (?)",(id,))
        db.commit()
        cursor.execute(f"INSERT INTO Active_users VALUES('{client[0]}','{client[1]}','{client[2]}','{info[0]}','{info[1]}','{info[2]}','{info[3]}','{info[4]}','{info[5]}')")
        db.commit()
        db.close()
        return "Operation was successfull"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def unregisterClient(info): #function is called
    t = info.split("|")
    id = t[3]
    db1 = sqlite3.connect("Active_users.sqlite")
    db2 = sqlite3.connect("InActive_users.sqlite")
    try:
        cursor1 = db1.cursor()
        cursor1.execute(f"SELECT * FROM Active_users WHERE id = (?)", (id,))
        l = cursor1.fetchall()
        client = l[0]
        client = list(client)
        cursor1.execute(f"DELETE FROM Active_users WHERE id = (?)", (id,))
        cursor2 = db2.cursor()
        cursor2.execute(
            f"INSERT INTO InActive_users VALUES('{client[0]}','{client[1]}','{client[2]}','{client[3]}','{client[4]}','{client[5]}','{client[6]}','{client[7]}','{client[8]}')")
        db1.commit()
        db2.commit()
        db1.close()
        db2.close()
        return "Operation was successfull"
    except Exception as e:
        db1.close()
        db2.close()
        return "Something went wrong " + str(e)
def registerMovie(info):
    t=info.split("|")
    db = sqlite3.connect("Active_movies.sqlite")
    db2 = sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"""INSERT INTO Active_movies VALUES(
                        '{t[0]}',
                        '{t[1]}',
                        '{t[2]}',
                        '{t[3]}',
                        '{t[4]}',
                        '{t[5]}',
                        '{t[6]}',
                        '{t[7]}')""")
        cursor2=db2.cursor()
        cursor2.execute("SELECT * FROM ScreeningRooms WHERE id = (?)",(t[7],))
        records=cursor2.fetchall()
        cursor2.execute("UPDATE ScreeningRooms SET moviesId = (?) WHERE id = (?)",(records[0][2]+","+t[0],t[7]))
        db2.commit()
        db2.close()
        db.commit()
        db.close()
        return "Operation was successfull"
    except Exception as e:
        db.close()
        db2.close()
        return "Something went wrong " + str(e)
def registerScreeningRoom(info):
    t=info.split("|")
    db=sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"INSERT INTO ScreeningRooms VALUES('{t[0]}','','')")
        db.commit()
        db.close()
        return "Operation was successfull"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def endMovie(info):
    t=info.split("|")
    id = t[0]
    db1 = sqlite3.connect("Active_movies.sqlite")
    db2 = sqlite3.connect("InActive_movies.sqlite")
    try:
        cursor1 = db1.cursor()
        cursor2 = db2.cursor()
        cursor1.execute(f"SELECT * FROM Active_movies WHERE id = (?)",(id,))
        list = cursor1.fetchall()
        movie = list[0]
        cursor1.execute(f"DELETE FROM Active_movies WHERE id = (?)", (id,))
        db1.commit()
        cursor2.execute(f"INSERT INTO InActive_movies VALUES('{movie[0]}','{movie[1]}','{movie[2]}','{movie[3]}','{movie[4]}','{movie[5]}'','{movie[6]}','{movie[7]}')")
        db2.commit()
        db1.close()
        db2.close()
        return "Operation was successfull"
    except Exception as e:
        db1.close()
        db2.close()
        return "Something went wrong " + str(e)
def deleteMovie(info,active):
    name=active+"Active_movies"
    t=info.split("|")
    id = t[0]
    db=sqlite3.connect(name+".sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"DELETE FROM {name} WHERE id = (?)",(id,))
        db.commit()
        db.close()
        return "Operation was successfull"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def retrieveScreeningRooms():
    db=sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor=db.cursor()
        cursor.execute(f"SELECT * FROM ScreeningRooms ")
        t=cursor.fetchall()
        s = ""
        for room in t:
            for element in room:
                s+=element+"|"
            s=s[:len(s)-1]
            s+="&"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def retrieveMovies():
    db = sqlite3.connect("Active_movies.sqlite")
    try:
        cursor=db.cursor()
        cursor.execute(f"SELECT * FROM Active_movies")
        movies=cursor.fetchall()
        s = ""
        for movie in movies:
            for element in movie:
                s+=element+"|"
            s=s[:len(s)-1]
            s+="&"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def updateScreeningRoom(info):
    screeningRoom = info.split("|")
    db = sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        id = screeningRoom[0]
        volume = screeningRoom[1]
        moviesId= screeningRoom[2]
        cursor.execute(f"Update ScreeningRooms set volume = '{volume}', moviesId = '{moviesId}' WHERE id = (?)",(id,))
        db.commit()
        db.close()
        return "Successfully updated screeningRoom of id = " + id
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def retrieveUser(login):
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE login = (?)",(login,))
        user = cursor.fetchall()[0]
        s=""
        for a in range(len(user)):
            if a<3:
                continue
            s+=user[a]+"|"
        s=s[:len(s)-1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def clientLogin(info):
    t = info.split("|")
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute("SELECT * FROM Active_users WHERE login = (?) AND password = (?)", (t[0], t[1]))
        users = cursor.fetchall()
        db.close()
        if (len(users) != 0):
            return "CanLog"
        else:
            return "CannotLog"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def checkLoginAndEmail(info):
    db = sqlite3.connect("Active_users.sqlite")
    info=info.split("|")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE login = (?) OR email = (?)", (info[0],info[1]))
        t = cursor.fetchall()
        db.close()
        if len(t)==0:
            return "0"
        else:
            return "1"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def canAdminLog(info):
    t = info.split("|")
    db = sqlite3.connect("AdminData.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute("SELECT * FROM AdminData WHERE login = (?) AND password = (?)",(t[0],t[1]))
        admins = cursor.fetchall()
        db.close()
        if(len(admins)!=0):
            return "CanLog"
        else:
            return "CannotLog"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def deleteRoom(id):
    t = id.split("|")
    id = t[0]
    db = sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"DELETE FROM ScreeningRooms WHERE id = (?)", (id,))
        db.commit()
        db.close()
        return "Operation was successfull"
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def getUsersVulnerableData(info):
    t = info.split("|")
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE id = (?)", (t[0],))
        user = cursor.fetchall()[0]
        s = ""
        for a in range(len(user)):
            if a > 2:
                break
            s += user[a] + "|"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def getIdByLogin(info):
    t = info.split("|")
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE login = (?)", (t[0],))
        user = cursor.fetchall()[0]
        return user[6]
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def retrieveUserByID(id):
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users WHERE id = (?)", (id,))
        user = cursor.fetchall()[0]
        s = ""
        for a in range(len(user)):
            if a < 3:
                continue
            s += user[a] + "|"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def retrieveScreeningRoomByID(id):
    db = sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM ScreeningRooms WHERE id = (?)", (id,))
        room = cursor.fetchall()[0]
        s = ""
        for a in range(len(room)):
            s += room[a] + "|"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def retrieveMovieByID(id):
    db = sqlite3.connect("Active_movies.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_movies WHERE id = (?)", (id,))
        movie = cursor.fetchall()[0]
        s = ""
        for a in range(len(movie)):
            s += movie[a] + "|"
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def getUsersIDs(info):
    db = sqlite3.connect("Active_users.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_users")
        users = cursor.fetchall()
        s = ""
        for user in users:
            s += user[6] + ","
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)

def getMoviesIDs(info):
    db = sqlite3.connect("Active_movies.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM Active_movies")
        movies = cursor.fetchall()
        s = ""
        for movie in movies:
            s += movie[0] + ","
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)
def getScreeningRoomsIDs(info):
    db = sqlite3.connect("ScreeningRooms.sqlite")
    try:
        cursor = db.cursor()
        cursor.execute(f"SELECT * FROM ScreeningRooms")
        rooms = cursor.fetchall()
        s = ""
        for room in rooms:
            s += room[0] + ","
        s = s[:len(s) - 1]
        db.close()
        return s
    except Exception as e:
        db.close()
        return "Something went wrong " + str(e)