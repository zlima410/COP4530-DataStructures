#include "passserver.h"

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
