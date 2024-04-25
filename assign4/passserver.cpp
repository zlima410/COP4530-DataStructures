#include "passserver.h"

// constructor that calls the HashTable constructor
PassServer::PassServer(size_t size = 101) : h(size) {}

// destructor
PassServer::~PassServer() {
    h.clear();
}

// calls the HashTable version of load()
bool load(const char *filename) {
    return h.load(filename);
}

// adds an encrypted password based on the KV value
bool addUser(std::pair<string,  string> & kv) {
    return h.insert(make_pair(kv.first, encrypt(kv.second)));
}

// 
bool addUser(std::pair<string,  string> && kv) {
    pair<string, string> encryptKV(std::move(kv));
    return addUser(encryptKV);
}

bool removeUser(const string & k) {
    return h.remove(k);
}

bool changePassword(const std::pair<string, string> &p, const string & newpassword) {
    if (!h.contains(p.first))
        return false;
    string encryptedNewPassword = encrypt(newpassword);
    if (encryptedNewPassword == p.second)
        return false;
    h.remove(p.first);
    h.insert(make_pair(p.first, encryptedNewPassword));
    return true; 
}

bool find(const string & user) {
    return h.contains(user);
}

void dump() {
    h.dump();
}

size_t size() {
    return h.size();
}

bool write_to_file(const char *filename) {
    return h.write_to_file(filename);
}

HashTable<string, string> h;

// Xian: in a shell, type "man crypt", and the MD5 can be found (which uses 22 characters of the password), and the usage will be shown as well.
// Note that it takes c_str, char [], not string directly as the input arguments. 
string PassServer::encrypt(const string & str) {
        char salt[] = "$1$########";
        char * password = new char [35];
        strcpy(password, crypt(str.c_str(), salt));

        string pword(password);
        string delim = "$";
        int pos = pword.find(delim, 0);
        pos = pword.find(delim, pos+1);
        pos = pword.find(delim, pos+1);
        pword.erase(0, pos+1);
        return pword;
	/*char salt[] = "$1$########";
	string ret = crypt(str.c_str(), salt);
	return ret.substr(1, 22);*/
}
