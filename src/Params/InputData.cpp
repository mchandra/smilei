#include "InputData.h"
#include <sstream>

using namespace std;

InputData::InputData():namelist("") {
}


bool BothAreSpaces(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

string InputData::cleanString(string str) {
    str=str.substr(0, str.find('#'));
    str=str.substr(0, str.find('!'));
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    const string whiteSpaces( " \f\n\r\t\v" );
    size_t pos = str.find_last_not_of( whiteSpaces );
    str.erase( pos + 1 );
    pos = str.find_first_not_of( whiteSpaces );
    str.erase( 0, pos );
    std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
    str.erase(new_end, str.end());
    return str;
}

void InputData::write(string filename=string()) {
    ofstream ostr(filename.c_str());
    if (ostr.is_open()) {
        ostr << "# smilei " << __VERSION << endl << endl;
        write(ostr);
    } else {
        write(cerr);
    }
}

void InputData::write(ostream &ostr) {
    for(vector<pair<string , vector<pair<string,string> > > >::iterator it_type = allData.begin(); it_type != allData.end(); it_type++) {
        if (!it_type->first.empty()) ostr << it_type->first << endl;
        for(vector<pair<string, string> >::iterator it_type2 = it_type->second.begin(); it_type2 != it_type->second.end(); it_type2++) {
            if (!it_type->first.empty()) ostr << "\t";
            ostr << it_type2->first << " = " << it_type2->second << endl;
        }
        if (!it_type->first.empty()) ostr << "end" << endl;
        ostr << endl;
    }
}

void InputData::parseStream() {
    if (namelist.empty()) ERROR("namelist is empty");
    
    stringstream my_stream(namelist);
    allData.clear();

    vector<pair <string,string> > defaultGroupVec;
    vector<pair <string,string> > thisGroup;

    string group("");
    string strLine("");
    while (getline(my_stream, strLine)) {
        strLine=cleanString(strLine);
        if (!strLine.empty()) {
            if (strLine.find('=') == string::npos) {
                if (strLine == "end") {
                    allData.push_back(make_pair(group,thisGroup));
                    group.clear();
                    thisGroup.clear();
                } else {
                    group=strLine;
                }
            } else {
                stringstream ss(strLine);
                string item;
                while(getline(ss, item, ',')) {
                    item=cleanString(item);
                    size_t posEqual=item.find('=');
                    string left=cleanString(item.substr(0,posEqual));
                    string right=cleanString(item.substr(posEqual+1));
                    if (group.empty()) {
                        defaultGroupVec.push_back(make_pair(left,right));
                    } else {
                        thisGroup.push_back(make_pair(left,right));
                    }
                }
            }
        }
    }
    
    if (!group.empty()) ERROR("Final group "<< group << " not closed. Check the namelist");

    // this wil put the default empty group "" in front of others
    std::reverse( allData.begin(), allData.end() );
    allData.push_back(make_pair("",defaultGroupVec));
    std::reverse( allData.begin(), allData.end() );
    
}


void InputData::readFile(string filename) {

    ifstream istr(filename.c_str());

    string strLine ="";
    namelist.clear();

    if (istr.is_open()) {
        while (getline(istr, strLine)) {
            strLine=cleanString(strLine);
            if (!strLine.empty()) namelist += strLine + "\n";
        }
    } else {
        ERROR("File " << filename << " does not exists");
    }
    namelist +="\n";
    
    
    unsigned long seedTime=0;
    if (!extract("random_seed",seedTime)) {
        RELEASEEXEC(seedTime=time(NULL));
        stringstream ss;
        ss << "random_seed = " << seedTime << endl;
        namelist+=ss.str();
    }
        
    size_t i = namelist.rfind('.', namelist.length( ));
    if (i != string::npos) {
        filename=filename.substr(0, i);
    }    
    write(filename+".parsed");
    
}

bool InputData::existGroup(std::string groupName, unsigned int occurrenceGroup) {
    unsigned int n_occur_group=0;
    for (vector<pair<string , vector<pair<string,string> > > >::iterator  it_type = allData.begin(); it_type != allData.end(); it_type++) {
        if (groupName == it_type->first) {
            if (occurrenceGroup==n_occur_group) {
                return true;
            }
            n_occur_group++;
        }
    }
    return false;
}


