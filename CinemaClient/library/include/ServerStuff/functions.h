#ifndef INTRODUCTIONPROJECT_FUNCTIONS_H
#define INTRODUCTIONPROJECT_FUNCTIONS_H
#include "typedefs.h"
#include <vector>
#include <string>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;
std::string convertMovieToStr(MoviePtr movie);
std::string convertClientToStr(ClientPtr client);
std::string convertScreeningRoomToStr(ScreeningRoomPtr screeningRoom);
MoviePtr convertStringToMovie(std::string info,ScreeningRoomRepository &SRP);
ScreeningRoomPtr convertStringToScreeningRoom(std::string info,MovieRepository &MR);
ClientPtr convertStringToClient(std::string info,MovieRepository &MR);
std::vector<std::string> split(char* t,int len,std::string delim);
std::vector<std::string> split(std::string str,std::string delim);
std::vector<std::string> exchangeInfoWithServer(std::string func_name, std::string message);
void strip(std::string& str);
bool retrieveRepositoriesState(MovieRepository &MR, ScreeningRoomRepository &SRR);
SegmentType ConvertTo(std::string letter);
pt::ptime convertStringToDate(std::string date);
void retrieveDataBases(ClientManager &CM,MovieManager &MM, ScreeningRoomManager &SRM);
void retrieveActiveUsers(ClientRepository &CR,MovieRepository &MR);
int getID();
bool isNumber(const std::string& str);
SegmentType convertNumToSegment(int num);

#endif //INTRODUCTIONPROJECT_FUNCTIONS_H
