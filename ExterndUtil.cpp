#include "ExterndUtil.h"

#define MAX_TEXT 1024
using namespace std;
using namespace ExternUtility;

/************************************************************************/
/*                                 StringRegex                          */
/************************************************************************/
vector<string> StringRegex::regexFindAllString(const string& src, const string& regexS, flag_type optionType)
{
    std::regex regx;
    try
    {
        regx.assign(regexS, optionType);
    }
    catch(const std::regex_error& e)
    {
        cout << "regular expression["<<regexS<<"] exception:" << e.what() << endl;
        return vector<string>();
    }
    
    vector<string> rsltVecStr;
    rsltVecStr.clear();

    auto resltBegin = sregex_iterator(src.begin(), src.end(), regx);
    auto resltEnd = std::sregex_iterator();
    for (std::sregex_iterator index = resltBegin; index != resltEnd; ++index)
    {
        std::smatch match = *index;
        // cout << (index - resltBegin) << endl;
        rsltVecStr.push_back(match.str());
    }
    return rsltVecStr;
}


bool StringRegex::regexMacth(const string& src, const string& regexS, flag_type optionType)
{
    std::regex regx;
    try
    {
        regx.assign(regexS, optionType);
    }
    catch (const std::regex_error& e)
    {
        cout << "regular expression[" << regexS << "] exception:" << e.what() << endl;
        return false;
    }
    std::smatch matchRslt;
    return std::regex_match(src, matchRslt, regx);
}

bool StringRegex::regexSearch(const string& src, const string& regexS, flag_type optionType)
{
    std::regex regx;
    try
    {
        regx.assign(regexS, optionType);
    }
    catch (const std::regex_error& e)
    {
        cout << "regular expression[" << regexS << "] exception:" << e.what() << endl;
        return false;
    }
    std::smatch matchRslt;
    return std::regex_search(src, matchRslt, regx);
}

/************************************************************************/
/*                                 StringUtility                        */
/************************************************************************/
int StringUtility::str_find(const string& srcStr, const string& subStr, int startFindIndex /* = 0 */)
{
    if (srcStr.empty())
    {
        return string::npos;
    }
#ifdef _FIND_FIRST_
    int findIndex = string::npos;
    while (string::npos != (findIndex = srcStr.find_first_of(subStr, startFindIndex)))
    {
        if (!srcStr.substr(findIndex, subStr.length()).compare(subStr))
        {
            return findIndex;
        }
        else
        {
            startFindIndex = findIndex + 1;
        }
    }

    return string::npos;
#else
    return srcStr.find(subStr, startFindIndex);
#endif //_FIND_FIRST_
}

void StringUtility::str_split(const string& srcStr, const string& splitStr, vector<string>& destVec)
{
    if (srcStr.empty())
    {
        return;
    }

    destVec.clear();
    int splitIndex = string::npos;
    int startFindIndex = 0;
    while (string::npos != (splitIndex = StringUtility::str_find(srcStr, splitStr, startFindIndex)))
    {
        if (splitIndex == 0)
        {
            destVec.push_back(string());
        }
        else
        {
            destVec.push_back(srcStr.substr(startFindIndex, splitIndex - startFindIndex));
        }
        startFindIndex = splitIndex + splitStr.length();
    }
    if (startFindIndex <= srcStr.length())
    {
        destVec.push_back(srcStr.substr(startFindIndex, srcStr.length() - startFindIndex));
    }
}

void StringUtility::str_replace(string& srcStr, const string& destStr, const string& replaceStr)
{
    if (srcStr.empty())
    {
        return;
    }

    vector<string> splitVec;

    StringUtility::str_split(srcStr, destStr, splitVec);
    int index = 0;
    srcStr.clear();
    for (auto& val : splitVec)
    {
        if (index + 1 < splitVec.size())
        {
            srcStr += splitVec.at(index) + replaceStr;
        }
        else
        {
            srcStr += splitVec.at(index);
        }
        index++;
    }
}

/************************************************************************/
/*                                 DebugUtility                        */
/************************************************************************/
void DebugUtility::printDebug(char *logMsg, ...)
{
#ifdef _DEBUG_
    string strLog = "";
#ifdef WIN32
    va_list argList;
    char cbuffer[MAX_TEXT + 1] = "";
    va_start(argList, logMsg);

    void *argp = va_arg(argList, void *);//T va_arg( va_list ap, T );

    vsnprintf(cbuffer, sizeof(cbuffer) - 1, logMsg, argList);
    va_end(argList);
#else
    va_list argList;
    char cbuffer[MAX_TEXT + 1] = "";
    va_start(argList, logMsg);
    vsnprintf(cbuffer, MAX_TEXT + 1, logMsg, argList);
    va_end(argList);
#endif //WIN32

    strLog.append(":");
    strLog.append(cbuffer);
    cout << "DEBUG:" << cbuffer << endl;
#endif //_DEBUG_
}

/************************************************************************/
/*                                 WINCodeConvert                       */
/************************************************************************/
#ifdef WIN32
#include <Windows.h>
#include <cstdlib>
#else
#include <locale.h>
#include <stdlib.h>
//将多字节编码转换为宽字节编码
//size_t mbstowcs(wchar_t* dest, const char* src, size_t max);
//将宽字节编码转换为多字节编码
//size_t wcstombs(char* dest, const wchar_t* src, size_t max);
// iconv
#endif
/**
#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation
 */
//gbk转UTF-8
string WINCodeConvert::GbkToUtf8(const std::string& strGbk)//传入的strGbk是GBK编码
{
#ifdef WIN32
    //gbk转unicode
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode, len);

    //unicode转UTF-8
    len = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char * strUtf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, strUtf8, len, NULL, NULL);

    std::string strTemp(strUtf8);//此时的strTemp是UTF-8编码
    delete[]strUnicode;
    delete[]strUtf8;
    strUnicode = NULL;
    strUtf8 = NULL;
    return strTemp;
#else
    if (NULL == setlocale(LC_ALL, "zh_CN.gbk"))     //设置转换为unicode前的编码为gbk编码        
    {
        return string();
    }
    int unicodeCNum=mbstowcs(NULL,strGbk.c_str(),0)*2+1;
    wchar_t* wcharStr = new wchar_t[unicodeCNum];

    mbstowcs(wcharStr,strGbk.c_str(),unicodeCNum-1);

    if (NULL == setlocale(LC_ALL, "zh_CN.utf8"))    //设置目标字符串编码为utf8编码
    {
        delete[] wcharStr;
        wcharStr = NULL;
        return string();
    }
    unicodeCNum=wcstombs(NULL,wcharStr,0)+1;     //计算待转换的字节数
    char* destStr = new char[unicodeCNum];
    wcstombs(destStr,wcharStr,unicodeCNum-1);
    string retStr(destStr);
    delete[] wcharStr;
    wcharStr = NULL;

    delete[] destStr;
    destStr = NULL;

    return retStr;
#endif
}

//UTF-8转gbk
string WINCodeConvert::Utf8ToGbk(const std::string& strUtf8)//传入的strUtf8是UTF-8编码
{
#ifdef WIN32
    //UTF-8转unicode
    int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
    wchar_t * strUnicode = new wchar_t[len];//len = 2
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode, len);

    //unicode转gbk
    len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];//len=3 本来为2，但是char*后面自动加上了\0
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);//此时的strTemp是GBK编码
    delete[]strUnicode;
    delete[]strGbk;
    strUnicode = NULL;
    strGbk = NULL;
    return strTemp;
#else
    if (setlocale(LC_ALL, "zh_CN.utf8")==NULL)
    {
        return string();
    }

    int codeCNum = mbstowcs(NULL,strUtf8.c_str(),0)*2+1;
    wchar_t* wcharStr = new wchar_t[codeCNum];
    mbstowcs(wcharStr, strUtf8.c_str(), codeCNum - 1);

    if (setlocale(LC_ALL, "zh_CN.gbk") == NULL)
    {
        delete wcharStr;
        wcharStr = NULL;
        return string();
    }
    codeCNum = wcstombs(NULL,wcharStr,0)+1;
    char* destStr = new char[codeCNum];
    wcstombs(destStr, wcharStr, codeCNum - 1);
    string retStr(destStr);

    delete[] destStr;
    destStr = NULL;
    return retStr;
#endif
}

//gbk转unicode 
wstring WINCodeConvert::GbkToUnicode(const std::string& strGbk)//返回值是wstring
{
#ifdef WIN32
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode, len);

    std::wstring strTemp(strUnicode);//此时的strTemp是Unicode编码
    delete[]strUnicode;
    strUnicode = NULL;
    return strTemp;
#else
    if (setlocale(LC_ALL, "zh_CN.gbk") == NULL)
    {
        return wstring();
    }

    int codeNum = mbstowcs(NULL, strGbk.c_str(), 0)*2+1;
    wchar_t* destStr = new wchar_t[codeNum];
    mbstowcs(destStr, strGbk.c_str(), codeNum - 1);

    wstring retStr(destStr);

    delete[] destStr;
    destStr = NULL;

    return destStr;
#endif
}

//Unicode转gbk
string WINCodeConvert::UnicodeToGbk(const std::wstring& strUnicode)//参数是wstring
{
#ifdef WIN32
    int len = WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];//len=3 本来为2，但是char*后面自动加上了\0
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);//此时的strTemp是GBK编码
    delete[]strGbk;
    strGbk = NULL;
    return strTemp;
#else
    if (setlocale(LC_ALL, "zh_CN.gbk") == NULL)
    {
        return string();
    }
    int codeNum = wcstombs(NULL, strUnicode.c_str(), 0) + 1;
    char* destStr = new char[codeNum];
    wcstombs(destStr, strUnicode.c_str(), codeNum - 1);

    string retStr(destStr);

    delete[] destStr;
    destStr = NULL;
    return retStr;
#endif
}

wstring WINCodeConvert::charToWCHAR(char *srcStr)
{
#ifdef WIN32
    int w_nlen = MultiByteToWideChar(CP_ACP, 0, srcStr, -1, NULL, 0);
    wchar_t *ret = new wchar_t[w_nlen];
    wmemset(ret, 0, sizeof(ret));
    MultiByteToWideChar(CP_ACP, 0, srcStr, -1, ret, w_nlen);
    wstring retStr(ret);

    delete[] ret;
    ret = NULL;
    return retStr;
#else
    int codeNum = mbstowcs(NULL, srcStr, 0)*2+1;
    wchar_t* destStr = new wchar_t[codeNum];
    mbstowcs(destStr, srcStr, codeNum - 1);
    wstring retStr(destStr);

    delete[] destStr;
    destStr = NULL;
    return retStr;
#endif
}

string WINCodeConvert::wcharToCHAR(wchar_t *srcStr)
{
#ifdef WIN32
    int w_nlen = WideCharToMultiByte(CP_ACP, 0, srcStr, -1, NULL, 0, NULL, false);
    char *ret = new char[w_nlen];
    memset(ret, 0, w_nlen);
    WideCharToMultiByte(CP_ACP, 0, srcStr, -1, ret, w_nlen, NULL, false);
    string retStr(ret);

    delete[] ret;
    ret = NULL;
    return ret;
#else
    int codeNum = wcstombs(NULL, srcStr, 0) + 1;
    char* destStr = new char[codeNum];
    wcstombs(destStr, srcStr, codeNum - 1);

    string retStr(destStr);

    delete destStr;
    destStr = NULL;

    return retStr;
#endif
}

/************************************************************************/
/*                                 XMLParser                            */
/************************************************************************/
string XMLParser::getNodeTree(XERCES_CPP_NAMESPACE::DOMDocument* doc, const string& xmlPath, const int itemIndex /*= 0*/)
{
    if (doc == NULL || xmlPath.empty())
    {
        return string();
    }

    DOMElement* root_element = doc->getDocumentElement();
    if (root_element == NULL)
    {
        cout << "Cannot get Parent node" << endl;
        return string();
    }

    string nodeValue("");
    XMLCh* toXmlChar = XMLString::transcode(xmlPath.c_str());
    DOMXPathResult *xmlResult(NULL);

    try
    {
        xmlResult = doc->evaluate(toXmlChar, root_element, NULL, DOMXPathResult::UNORDERED_NODE_SNAPSHOT_TYPE, NULL);
    }
    catch (DOMException& exception)
    {
        cout << "evaluate xmlPath[" << xmlPath << "] Exception is [" << XMLString::transcode(exception.msg) << "]" << endl;
        return nodeValue;
    }

    if (xmlResult->getSnapshotLength() < itemIndex + 1)
    {
        cout << "the itemIndex[" << itemIndex << "] out of the xmlPath[" << xmlPath << "] result size[" << xmlResult->getSnapshotLength() << "]" << endl;
        return nodeValue;
    }

    xmlResult->snapshotItem(itemIndex);
    DOMNode* xmlNode = xmlResult->getNodeValue();

    DOMImplementation *pImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
    DOMLSSerializer *pSerializer = ((DOMImplementationLS*)pImplementation)->createLSSerializer();
    nodeValue = XMLString::transcode(pSerializer->writeToString(xmlNode));

    pSerializer->release();
    xmlResult->release();
    XMLString::release(&toXmlChar);
    int startPos = nodeValue.find(">");
    
    nodeValue = nodeValue.substr(startPos+1, nodeValue.find_last_of("/") - startPos-1-1);
    return nodeValue;
}

#define XPATH_SEP "/"
int XMLParser::add_node(XERCES_CPP_NAMESPACE::DOMDocument* doc, DOMElement* root, const string& x_path, const string& text_context /*= ""*/, const int index /*= 0*/, const string& parent_path /*= ""*/)
{
    if (NULL == doc || NULL == root) {
        cout << "NULL DOMDocument Or Root element is given, please check ! " << endl;
        return -1;
    }

    DOMXPathResult* result_dom = doc->evaluate(XMLString::transcode(x_path.c_str()), root, NULL, DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE, NULL);
    result_dom->snapshotItem(index);
    DOMNode* parent_node = result_dom->getNodeValue();
    result_dom->release();
    // test if the node exists, if exists, just set the node value
    if (NULL != parent_node) {
        if (0 != text_context.size()) {
            parent_node->setTextContent(XMLString::transcode(text_context.c_str()));
        }
        return 0;
    }
    // find the parent node to test if the parent node exists
    // the last / index to separate the parent and current node
    size_t last_slash = x_path.find_last_of(XPATH_SEP);
    if (last_slash == string::npos) {
        cout << "Wrong XPath [%s] given , please check ! " << endl;
        return -1;
    }
    if (0 == last_slash) {
        cout << "Error, the last [/] is the first character of the XPath[%s]! Cannot add root element by XPath ! " << endl;
        return -1;
    }
    // if extra / give at the end of the x path, just ignore it
    if (last_slash == x_path.length()) {
        last_slash = x_path.substr(0, x_path.length() - 1).find_last_of(XPATH_SEP);
    }

    // variable represents current index
    int cur_index=-1;
    // get the current x path
    string curr_xpath = x_path.substr(0, last_slash);
    // get the parent node to append the new node
    result_dom = doc->evaluate(XMLString::transcode(/*x_path.substr(0,last_slash)*/curr_xpath.c_str()), root, NULL, DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE, NULL);
    // test if we can find the parent item, false means the parent node not found
    // we have to call this function recursively to add the parent node
    // If we have hit the node list parent path, just set the index to 0, in order to fetch the node
    // list parent node
    if (0 == parent_path.size() || (0 == strcmp(curr_xpath.c_str(), parent_path.c_str())) || curr_xpath.size() < parent_path.size()) {
        cur_index = 0;
    }
    else {
        cur_index = index;
    }

    if (result_dom->getSnapshotLength() > cur_index+1)
    {
        return -1;
    }

    if (false == result_dom->snapshotItem(cur_index/*index*/)) {
        result_dom->release();
        // If the parent path is specified, test if we hit the node list root element, if we hit, just add the 
        // node without index.
        add_node(doc, root,/*x_path.substr(0,last_slash)*/curr_xpath, "",/*index*/cur_index, parent_path);
        result_dom = doc->evaluate(XMLString::transcode(/*x_path.substr(0,last_slash)*/curr_xpath.c_str()), root, NULL, DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE, NULL);
    }
    result_dom->snapshotItem(cur_index);
    parent_node = result_dom->getNodeValue();
    if (NULL == parent_node) {
        cout << "Root node in the XPath[%s] not found, failed to add node ! " << endl;
        return -1;
    }
    DOMElement* new_node = doc->createElement(XMLString::transcode(x_path.substr(last_slash + 1).c_str()));
    if (0 != text_context.length()) {
        ((DOMNode*)new_node)->setTextContent(XMLString::transcode(text_context.c_str()));
    }
    parent_node->appendChild(new_node);
    result_dom->release();
    return 0;
}