#include "EmojiParser.h"

EmojiParser EmojiParser::defaultParser;

EmojiParser::EmojiParser()
{
    //std::vector<std::string> tags({ "88","am","bs","bz","ch","cool","dhq","dn","fd","gz","han","hx","hxiao","hxiu" });
    std::vector<std::string> tags;
    tags.push_back("88"); tags.push_back("am"); tags.push_back("bs"); tags.push_back("bz"); tags.push_back("ch");
    tags.push_back("cool"); tags.push_back("dhq"); tags.push_back("dn"); tags.push_back("fd"); tags.push_back("gz");
    tags.push_back("han"); tags.push_back("hx"); tags.push_back("hxiao"); tags.push_back("hxiu");

    for (auto &str : tags)
        _handlers[":" + str] = UBB_TAG_HANDLER(EmojiParser::onTag_Emoji, this);
}

void EmojiParser::onTag_Emoji(const std::string & tagName, bool end, const std::string & attr, std::string & replacement)
{
    std::string str = tagName.substr(1);
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    replacement = "<img src='ui://Emoji/" + str + "'/>";
}
