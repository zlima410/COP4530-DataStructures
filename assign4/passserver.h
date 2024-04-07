#ifndef PASSSERVER_H
#define PASSSERVER_H
#include <sstream>
#include <string>
#include <cstring>
#include "hashtable.h"
// this shall be included on a macos for crypt() to be included
#include <unistd.h>
//#include <crypt.h>

using namespace std;
using namespace cop4530;

class PassServer {

  public:

    explicit PassServer(size_t size = 101);

    ~PassServer();

    bool load(const char *filename);

    bool addUser(std::pair<string,  string> & kv);

    bool addUser(std::pair<string,  string> && kv);

    bool removeUser(const string & k);

    bool changePassword(const std::pair<string, string> &p, const string & newpassword);

    bool find(const string & user) const;

    void dump() const;

    size_t size() const;

    bool write_to_file(const char *filename) const;

  private:

    HashTable<string, string> h;

    // Xian: in a shell, type "man crypt", and the MD5 can be found (which uses 22 characters of the password), and the usage will be shown as well.
    // Note that it takes c_str, char [], not string directly as the input arguments. 
    string encrypt(const string & str);
};

#endif
