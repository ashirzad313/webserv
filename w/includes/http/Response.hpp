#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <ctime>
#include <sys/stat.h>

struct Webserv;
struct HttpRequest;

class Response
{
	private:
		serverConfig	*choosed_server = nullptr;
		struct Route	*choosed_route = nullptr;

		std::string http_version;
		std::string status_code;
		std::string reason_phrase;

		std::map<std::string, std::string>  headers;
		std::string body = "";

		void	addHeader(const std::string& name, const std::string& value);
		bool	addBody(const std::string& file_path, bool is_bin);
		void	formError(int code, const Webserv& webserv);
		void	findRouteInConfig(const std::string& request_path);
		void	handleGET(std::string& full_path, const Webserv& webserv);
		void	handleDirRequest(std::string& full_path, const Webserv& webserv);
		void	serveFile(const std::string& full_path, const Webserv& webserv);
		bool	isMethodAllowed(const std::string& method);
		void	redirect(const Webserv& webserv);
		void	generateAutoindexHTML(const std::string& full_path, const Webserv& webserv);

		std::string	findFullPath(const std::string& request_path);
		std::string	checkContentType(std::string file, const Webserv& webserv);
		std::string takeGMTTime();
		std::string checkLastWriteTime(const char *path);


		void	handlePOST(const HttpRequest &request, const Webserv &webserv);
		void	handleDELETE(const HttpRequest &request, const Webserv &webserv);



	public:
		std::string findHeaderValue(const std::string& name,
			const std::map<std::string, std::string>& headers) const;
		void	chooseServer(int fd, const HttpRequest& request,
			std::vector<serverConfig>& servers);

		void	formResponse(const HttpRequest& request, const Webserv& webserv);
		void	sendResponse(int socket_fd);
};

#endif
