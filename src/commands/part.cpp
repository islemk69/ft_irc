#include "../../includes/commands.hpp"

// void	partCmd(Client *client, const Command &command, Server *server) {
// 	if (command.args.empty()){
// 		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
// 		return ;
// 	}
// 	Server::vecStr targetChannels = ft_split(command.args[0], ",");
// 	std::string reason = command.args.size() > 1 ? command.args[1] : "No reason";
// 	for (Server::vecStrIt it = targetChannels.begin(); it != targetChannels.end(); it++) {
// 		std::string targetChannel = *it;
// 		Channel *channel = server->getChannelByName(targetChannel);
// 		if (channel == NULL)
// 			Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, targetChannel));
// 		else if (!client->isOnChannel(targetChannel))
// 			Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, targetChannel));
// 		else
// 			client->leaveChannel(channel, reason);
// 	}
// }