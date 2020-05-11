#pragma once

#ifndef COVIDSIM_INFSTAT_H_INCLUDED_
#define COVIDSIM_INFSTAT_H_INCLUDED_

//// Infection Status definitons / labels (generally positive value indicates asymptomatic infection, negative value indicates symptomatic infection).
#define InfStat_Susceptible						0				//// Susceptible
#define InfStat_Latent							1				//// E or L (neither infectious nor symptomatic).
#define InfStat_InfectiousAlmostSymptomatic		-1				//// Infectious and about to become a case.
#define InfStat_InfectiousAsymptomaticNotCase	2				//// Not just asymptomatic, but also will not become symptomatic (i.e. a case.)
#define InfStat_Case							-2				//// case. Infectious and symptomatic.
#define InfStat_RecoveredFromAsymp				3				//// Recovered from asymptomatic infection
#define InfStat_RecoveredFromSymp				-3				//// Recovered from symptomatic infection
#define InfStat_Recovered						3				//// InfStat_Recovered (will use this for abs() values) so code reads correctly
#define InfStat_ImmuneAtStart					4				//// Immune at start of epidemic - used to model partially immune population. Distinct therefore from recovered, who recovered during runtime. Doesn't take negative values.
#define InfStat_Dead_WasAsymp					5				//// Dead was asymptomatic
#define InfStat_Dead_WasSymp					-5				//// Dead was symptomatic
#define InfStat_Dead							5				//// Dead (will use this for abs() values) so code reads correctly


#define NUM_SYMPTO_SEVERITY_CLASSES 4
#endif // COVIDSIM_INFSTAT_H_INCLUDED_
