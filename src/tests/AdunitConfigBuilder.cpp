//
// Created by lhumphreys on 10/05/2020.
//

#include "AdunitConfigBuilder.h"
namespace {
    constexpr const char* const defaultContent = R"CONFIG(
[Number of seed locations]
1

[Initial number of infecteds]
100


[Administrative unit to seed initial infection into]
0


[Population size]
66777534
[ONS pop proj]

[Fix population size at specified value]
1

[Number of countries to include]
1

[List of names of countries to include]
United_Kingdom

[Number of level 1 administrative units to include]
0

[List of level 1 administrative units to include]
East_Midlands	East_of_England	London	North_East	North_West	South_East	South_West	West_Midlands	Yorkshire_and_the_Humber	Northern_Ireland	North_Eastern_Scotland	Highlands_and_Islands	Eastern_Scotland	West_Central_Scotland	Southern_Scotland	East_Wales	West_Wales_and_The_Valleys

[Codes and country/province names for admin units]
540100	United_Kingdom	East_Midlands
540200	United_Kingdom	East_of_England
540300	United_Kingdom	London
540400	United_Kingdom	North_East
540500	United_Kingdom	North_West
540600	United_Kingdom	South_East
540700	United_Kingdom	South_West
540800	United_Kingdom	West_Midlands
540900	United_Kingdom	Yorkshire_and_the_Humber
541000	United_Kingdom	Northern_Ireland
541100	United_Kingdom	North_Eastern_Scotland
541200	United_Kingdom	Highlands_and_Islands
541300	United_Kingdom	Eastern_Scotland
541400	United_Kingdom	West_Central_Scotland
541500	United_Kingdom	Southern_Scotland
541600	United_Kingdom	East_Wales
541700	United_Kingdom	West_Wales_and_The_Valleys

[Mask for level 1 administrative units]
100000

[Divisor for level 1 administrative units]
100

[Divisor for countries]
100000

[Correct administrative unit populations]
0

[Age distribution of population]
0.057810002	0.060683584	0.05827917	0.054298865	0.060021798	0.066052894	0.069334292	0.067586774	0.06346124	0.063284341	0.068269448	0.066860984	0.057523138	0.04981529	0.049914383	0.035974234	0.050829564
[ONS proj for 2020]


[Household size distribution]
0.305305	0.342342	0.159159	0.136136	0.040040	0.011243	0.003677	0.001256	0.000453	0.000388
(ONS 2020 with IPUMS and national statistics)

[Correct age distribution after household allocation to exactly match specified demography]
1

[Include places]
1

[Place overlap matrix]
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1

(note this isn't used - currently assume identity matrix)

[Number of types of places]
4

[Proportion of age group 1 in place types]
0.976396125	0.98390173	0	0.37097869299999997

[Minimum age for age group 1 in place types]
5	11	18	16

[Maximum age for age group 1 in place types]
11	16	65	18

[Proportion of age group 2 in place types]
1	0.959727307	0.629021307	0.040272693000000026

[Minimum age for age group 2 in place types]
3	16	18	18

[Maximum age for age group 2 in place types]
5	18	21	21

[Proportion of age group 3 in place types]
0.005292966	0.006331515	0.064144615	0.742058813

[Minimum age for age group 3 in place types]
21	21	21	21

[Maximum age for age group 3 in place types]
65	65	65	65

[Kernel shape params for place types]
3 3 3 3


[Kernel scale params for place types]
4000  4000  4000  4000

[Mean size of place types]
230 1010  3300  14.28

(inc teachers)

[Number of closest places people pick from (0=all) for place types]
3 3 6 0

[Param 1 of place group size distribution]
25  25  100 10

[Power of place size distribution]
0 0 0 1.34

[Offset of place size distribution]
0 0 0 5.35

[Maximum of place size distribution]
0 0 0 5927

[Kernel type]
2

[Kernel scale]
4000

[Kernel Shape]
3

[Kernel resolution]
2000000

[Kernel higher resolution factor]
400

===================================
[Include holidays]
1

[Proportion of places remaining open during holidays by place type]
0 0 1 1

[Number of holidays]
9

[Holiday start times]
97	195	294	353	412	461	559	658	717


[Holiday durations]
15	51	7	15	7	15	51	7	15

===================================
)CONFIG";
}

std::unique_ptr<ConfigFile> AdunitConfigBuilder::BuildCfgFile(
        const std::string& fname) const
{
    return std::make_unique<ConfigFile>(fname, defaultContent);
}
