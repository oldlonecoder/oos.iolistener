

#include <lus/io/ansi_parser.h>

namespace lus::io
{



std::pair<rem::cc, ansi_parser::input_data> ansi_parser::parse(lfd &_fd)
{
    data = {};
    if(_fd.empty())
        return {rem::cc::empty,{}};
    /////////////////////////////////////////////////////
    /// Input size is 1: Either {CTRL/ALT/Command +}CHAR or ESCAPE:
    if(_fd.size() == 1)
    {
        if(data.kev = kbhit::query(*_fd); data.kev)
            return{rem::cc::accepted, data};
        data.kev = {kbhit::CHARACTER, *_fd, "char"};
        return {rem::cc::ready, data};
    }
    /////////////////////////////////////////////////////

    // We start CSI here : Keyboard or Mouse report:
    if(*_fd != 0x1b)
    {
        journal::status() << "unknown or unhandled input sequence from th econsole." << journal::eol;
        return {rem::cc::notimplemented,{}};
    }
    u64 seq = 0;
    u8  byt;
    _fd >> byt;
    do
    {
        seq |= (seq << 8) | byt;

    }while(!(_fd >> byt).empty());

    return {rem::cc::notimplemented, {}};
}

} // namespace lus::io
