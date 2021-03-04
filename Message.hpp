#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>
#include "Error.hpp"
#include "Channel.hpp"
#include "utils.hpp"

#define	BUFFER_SIZE		512

//:tolsun.oulu.fi SERVER csd.bu.edu 5 34 :BU Central Server
//서버 tolusun.oulu.fi는 5홉 떨어진 csd.bu.edu의 업 링크 토큰 "34"는 csd.bu.edu에 연결된 새로운 사용자나 서비스를 소개 할 때 tolsun.oulu.fi에 의해 사용됨

class Message
{
private:
	std::string					_dest; //csd.bu.edu

	// CR(13)-LF(10) 으로 끝나야 함
	std::string					_msg; //:tolsun.oulu.fi SERVER csd.bu.edu 5 34 :BU Central Server

	// 거쳐온 경로
	std::vector<std::string>	_paths;

	// 		*path;
	std::string					_prefix;

	// :tolsun.oulu.fi
	// command는 3자리 숫자거나 유효한 IRC 명령
	std::string					_command;

	// SERVER
	//param은 최대 15개
	std::vector<std::string>	_param;
	int							_size;
	// csd.bu.edu 5 34 :BU Central Server

	// 전송 -> 메세지를 만들어야 하니까 = 커맨드를 만들어야함 -> 팩토리

	// 수신 -> 문자열을 파싱 -> 커맨드 -> 실행

	// 전송 -> 메세지를 만든다 -> 문자열 조작 
	// 받는 -> 파싱 -> 


public:
	Message();
	Message(const char *msg);
	~Message();
	void			get_info();
	const int		get_size();
	const char		*get_msg();
	void			set_prefix(const char *prefix);
	void			inputPath(std::string path);
private:
	int				insert_string(int start, std::string str);

};

#endif