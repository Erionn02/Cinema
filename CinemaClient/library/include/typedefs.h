#ifndef INTRODUCTIONPROJECT_TYPEDEFS_H
#define INTRODUCTIONPROJECT_TYPEDEFS_H
#include <memory>
#include <functional>
#include <algorithm>
class Client;
class Ticket;
class Movie;
class ClientType;
class Junior;
class Senior;
class Concessionary;
class Regular;
class ScreeningRoom;
class ClientRepository ;
class MovieRepository;
class ScreeningRoomRepository;
class ClientManager;
class MovieManager;
class ScreeningRoomManager;
struct ar;
typedef enum SegmentType{A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,K=10,L=11,M=12,N=13,O=14,P=15,Q=16,R=17,S=18,T=19,U=20,V=21,W=22,X=23,Y=24,Z=25}SegmentType;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Ticket> TicketPtr;
typedef std::shared_ptr<Movie> MoviePtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Junior> JuniorPtr;
typedef std::shared_ptr<Senior> SeniorPtr;
typedef std::shared_ptr<Regular> RegularPtr;
typedef std::shared_ptr<ar> arPtr;
typedef std::shared_ptr<Concessionary> ConcessionaryPtr;
typedef std::shared_ptr<ScreeningRoom> ScreeningRoomPtr;
typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(TicketPtr)> TicketPredicate;
typedef std::function<bool(MoviePtr)> MoviePredicate;
typedef std::function<bool(ScreeningRoomPtr)> ScreeningRoomPredicate;
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
#endif //INTRODUCTIONPROJECT_TYPEDEFS_H
