#ifndef __EMOJIPARSER_H__
#define __EMOJIPARSER_H__

#include "FairyGUI.h"
#include "utils/UBBParser.h"

USING_NS_FGUI;

class EmojiParser : public UBBParser
{
public:
    static EmojiParser defaultParser;

    EmojiParser();

protected:
    void onTag_Emoji(const std::string& tagName, bool end, const std::string& attr, std::string& replacement);
};

#endif