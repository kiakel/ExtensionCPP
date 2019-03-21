//#pragma once
#ifndef EXTERNDUTIL_H
#define EXTERNDUTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMXPathResult.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/validators/schema/identity/XPathException.hpp>
#include <xercesc/dom/DOMDocument.hpp>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::istringstream;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::wstring;
using std::regex_constants::syntax_option_type;
using namespace XERCES_CPP_NAMESPACE;

namespace ExternUtility
{
    /*************************************************正则表达式********************************************************/
    class StringRegex
    {
    public:
        typedef std::regex_constants::syntax_option_type flag_type;
        static constexpr flag_type IgnoreCASE = std::regex_constants::icase; // 忽略大小写;
        static constexpr flag_type ECMAScript_REG = std::regex_constants::ECMAScript;
        static constexpr flag_type BASE_REG = std::regex_constants::basic; // POSIX, 基础正则表达式，"leftmost longest" matching rule
        static constexpr flag_type EXTERNED_REG = std::regex_constants::extended; // POSIX,扩展正则表达式，"leftmost longest" matching rule

    protected:
        StringRegex() {}
    public:
        /**
         * 从src字符串中筛选出所有满足regexS正则表达式的字符串
         * @param[in] src: 源字符串
         * @param[in] regexS: 正则表达式
         * @return: 利用正则表达式regexS在src中找出所有符合条件的子字符串
         */

        static vector<string> regexFindAllString(const string& src, const string& regexS, flag_type optionType=ECMAScript_REG);

        /**
         * 检查src字符串是否匹配regexS正则表达式的要求
         * @param[in] src: 源字符串
         * @param[int] regexS: 正则表达式
         * @return: 检查src是否满足regexS的要求，满足返回true；不满足返回false。
         */
        static bool regexMacth(const string& src, const string& regexS, flag_type optionType=ECMAScript_REG);

        /**
         * 检查src字符串是否匹配regexS正则表达式的要求
         * @param[in] src: 源字符串
         * @param[int] regexS: 正则表达式
         * @return: 检查src中某一连续截断子字符串是否满足regexS的要求，满足返回true；不满足返回false。
         */
        static bool regexSearch(const string& src, const string& regexS, flag_type optionType=ECMAScript_REG);


        /* regex_match 和 regex_search 差异
        std::regex re("Get|GetValue"); // 从字符串序列中查找Get或者GetValue字符串
        std::string strSequence1 = "GetValue";
        std::string strSequence2 = "GetValue setValue Get";
        std::smatch matchRslt;
        std::regex_search(strSequence1, matchRslt, re);
        // returns true, and matchRslt[0] is "Get",只要整个序列strSequence1中某一连续子字符串满足匹配要求就结束
        std::regex_match (strSequence1, matchRslt, re);
        // returns true, and matchRslt[0] is "GetValue"
        std::regex_search(strSequence2, matchRslt, re);
        // returns true, and matchRslt[0] is "Get"，GetValue的子字符串的"Get"
        std::regex_match (strSequence2, matchRslt, re);
        // returns false, regex_match要求整个字符序列strSequence2完全匹配Get或者GetValue，即strSequence2为"GetValue"或者"Get"时该方法返回true
        */

    };

    /*********************************************字符串************************************************************/
    class StringUtility
    {
    protected:
        StringUtility() {}
    public:
        /**
     * 检查子字符串subStr在源字符串strStr中的位置索引。
     */
        static int str_find(const string& srcStr, const string& subStr, int startFindIndex = 0);
        /**
         * 根据splitStr把srcStr拆分成n个子字符串并存放在destVec中
         */
        static void str_split(const string& srcStr, const string& splitStr, vector<string>& destVec);
        /**
         * 用replaceStr替换srcStr中的destStr
         */
        static void str_replace(string& srcStr, const string& destStr, const string& replaceStr);

        /**
         * 数字转string
         */
        template<class NumType>
        static string NumToString(NumType val)
        {
            stringstream strStream;
            strStream << std::fixed << std::setprecision(10) << val;//setprecision控制浮点数有效位数，与fixed连用控制小数点位数
            return strStream.str();
        }

        /**
         * string 转 数字
         */
        template<class NumType>
        static NumType StringToNum(string val)
        {
            istringstream iss(val);
            NumType num;
            iss >> num;
            return num;
        }
    };

    /*************************************************Debug输出*******************************************************/
    class DebugUtility
    {
    protected:
        DebugUtility() {}
    public:
        static void printDebug(char *logMsg, ...);
    };

    /*************************************************编码转换*****************************************************/
    class WINCodeConvert
    {
    protected:
        WINCodeConvert() {}
    public:
        //gbk转UTF-8
        static string GbkToUtf8(const std::string& strGbk);//UTF-8转gbk
        static string Utf8ToGbk(const std::string& strUtf8); //传入的strUtf8是UTF-8编码
        //gbk转unicode 
        static wstring GbkToUnicode(const std::string& strGbk); //返回值是wstring
        //Unicode转gbk
        static string UnicodeToGbk(const std::wstring& strUnicode);
        // char*转wchar_t*
        wstring charToWCHAR(char *s);
        //wchar_t* 转char*
        string wcharToCHAR(wchar_t *s);
    };


    /*************************************************XML 解析*************************************************/
    class XMLParser
    {
    public:
        XMLParser() :m_pXParser(NULL) { XMLInitialize(); }
        ~XMLParser() { XMLTerminate(); }
        /** function 解析一个xml字符串
         * @note
         * @param
         * @return
         * @warning
         * @exception
         * @see
         */
        XERCES_CPP_NAMESPACE::DOMDocument* parseXMLString(const string& xmlStr)
        {
            if (m_pXParser == NULL)
            {
                return NULL;
            }
            MemBufInputSource xmlBuff((const XMLByte*)(xmlStr.c_str()), xmlStr.length(), "");
            m_pXParser->parse(xmlBuff);

            return m_pXParser->getDocument();
        }

        /** function 解析一个xml文件
         * @note
         * @param
         * @return
         * @warning
         * @exception
         * @see
         */
        XERCES_CPP_NAMESPACE::DOMDocument* parseXMLFile(const string& xmlFilePath)
        {
            if (m_pXParser == NULL)
            {
                return NULL;
            }
            m_pXParser->parse(xmlFilePath.c_str());
            return m_pXParser->getDocument();
        }

        /** function 从解析的xml文档中获取某节点树分支
         * @note
         * @param
         * @return
         * @warning
         * @exception
         * @see
         */
        string getNodeTree(XERCES_CPP_NAMESPACE::DOMDocument* doc, const string& xmlPath, const int itemIndex = 0);

        /** function
         * @note 
         * @param 
         * @return 
         * @warning 
         * @exception 
         * @see 
         */
        int add_node(XERCES_CPP_NAMESPACE::DOMDocument* doc, DOMElement* root, const string& x_path, const string& text_context = "", const int index = 0, const string& parent_path = "");
    private:
        /** function
         * @note
         * @param
         * @return
         * @warning
         * @exception
         * @see
         */
        void XMLInitialize()
        {
            XMLPlatformUtils::Initialize();
            m_pXParser = new XercesDOMParser();
            m_pXParser->setValidationScheme(XercesDOMParser::Val_Never);
        }

        /** function
         * @note
         * @param
         * @return
         * @warning
         * @exception
         * @see
         */
        void XMLTerminate()
        {
            if (m_pXParser != NULL)
            {
                delete m_pXParser;
                m_pXParser = NULL;
            }
            XMLPlatformUtils::Terminate();
        }

    private:
        XercesDOMParser * m_pXParser;
    };// XMLParser
};// namespace

#endif //EXTERNDUTIL_H