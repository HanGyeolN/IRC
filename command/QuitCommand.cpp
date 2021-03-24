#include "QuitCommand.hpp"
#include "ft_irc.hpp"

// delete_member 함수 구현 필요
void	QuitCommand::run(IrcServer &irc)
{
	Socket	*socket;
	Member	*member;

	socket = irc.get_current_socket();
	if (socket->get_type() == CLIENT)
	{
		member = irc.get_member(socket->get_fd()); // 1. 멤버를 찾는다.
		_msg.set_prefix(member->get_nick()); // 2. 메세지를 전파하기 위해 닉네임을 프리픽스로 설정
		irc.delete_member(member->get_nick()); // 3. 멤버를 지운다.
		socket->~Socket();// 4. 소켓 연결을 끊는다.
		irc.send_msg_server(0, _msg.get_msg())// 5. 다른 서버에서도 _global_user에서 해당 유저를 지울 수 있도록 메세지를 보낸다.
	}
	else if (socket->get_type() == SERVER)
	{
		member = irc.get_member(_msg.get_prefix()); // 1. prefix로 멤버를 찾는다.
		irc.delete_member(member->get_nick()); // 2. 멤버를 지운다.
		irc.send_msg_server(socket->get_fd(), _msg.get_msg()); // 3. 다른서버에도 메세지를 보낸다.
	}
	else if (socket->get_type() == UNKNOWN)
	{
		member = irc.get_member(socket->get_fd()); // 1. fd값으로 멤버를 찾는다.
		if (member)
			irc.delete_member(socket->get_fd()); // 2. 멤버로 추가되어있으면 삭제한다.
		socket->~Socket(); // 3. 소켓 연결을 끊는다. 다른 서버에는 전송하지 않는다.
	}
}

QuitCommand::QuitCommand() : Command()
{
}

QuitCommand::~QuitCommand()
{
}

QuitCommand::QuitCommand(QuitCommand const &copy)
{
	_msg = copy._msg;
}

QuitCommand	&QuitCommand::operator=(QuitCommand const &ref)
{
	_msg = ref._msg;
	return (*this);
}