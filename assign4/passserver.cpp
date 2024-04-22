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
    string encryptPassword = encrypt(kv.second);
    pair<string, string> encryptKV(kv.first, encryptPassword);
    return h.insert(encryptKV);
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
    if (find(p.first)) {
        std::pair<string, string> oldEKV = std::make_pair(p.first, encrypt(p.second));
        if (h.match(oldEKV)) {
            std::pair<string, string> eKV = std::make_pair(p.first, encrypt(newpassword));
            if (!h.match(eKV))
                return h.insert(eKV);
            else
                return false;
        } else {
            return false;
        }
    } else {
        return false;
    }
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
