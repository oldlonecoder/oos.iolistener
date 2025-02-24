/******************************************************************************************
*   Copyright (C) ...,2025,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club / lussier.serge@gmail.com                            *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (Serge Lussier), unless otherwise specified.   *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/



#pragma once

#include <lus/io/lfd.h>
#include <lus/io/kbhit.h>
#include <lus/io/mouse.h>

namespace lus::io
{



//////////////////////////////////////////////////////////////////////
/// \brief The ansi_parser class
/// \note We parse either kbhit or mouse...
/// \author oldlonecoder Serge Lussier (serge.lussier@oldlonecoder.club)
///
class LUSIOLIB ansi_parser
{


public:

    union input_data
    {
        mouse mev;
        kbhit kev;
    } data{};

    ansi_parser() = default;
    ~ansi_parser() = default;

    std::pair<rem::cc, ansi_parser::input_data> parse(lfd& _fd); ///< Returns either key or mouse
private:
    rem::cc parse_kbhit(lfd& _fd);
    rem::cc parse_mouse(lfd& _fd);

    std::pair<rem::cc, std::vector<int>> parse_args(lfd& _fd);

};

} // namespace lus::io

