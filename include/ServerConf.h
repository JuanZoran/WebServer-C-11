#pragma mark
struct ServerConf
{
    ServerConf(
        const char *db_user,
        const char *db_password,
        const char *db_name,
        const char *db_host = "localhost",
        short db_port = 3306,
        short server_port = 12345);
    const char *db_user;
    const char *db_password;
    const char *db_name;
    const char *db_host;
    short db_port;
    const char *server_host;
    short server_port;
};

ServerConf::ServerConf(
    const char *db_user,
    const char *db_password,
    const char *db_name,
    const char *db_host,
    short db_port,
    short server_port) : db_user(db_user),
                         db_password(db_password),
                         db_name(db_name),
                         db_host(db_host),
                         db_port(db_port),
                         server_port(server_port) {}