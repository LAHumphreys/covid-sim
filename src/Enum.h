#pragma once

#ifndef COVIDSIM_ENUM_H_INCLUDED_
#define COVIDSIM_ENUM_H_INCLUDED_

enum PlaceType
{
    PrimarySchool   = 0,
    SecondarySchool = 1,
    University      = 2,
    Office          = 3,
    Count           = 4
};

enum Severity
{
    Asymptomatic           = -1,
    Mild                   = 0,
    ILI                    = 1,
    SARI                   = 2,
    Critical               = 3,
    RecoveringFromCritical = 4,
    Dead                   = 5,
    Recovered              = 6
};

#endif // COVIDSIM_ENUM_H_INCLUDED_
