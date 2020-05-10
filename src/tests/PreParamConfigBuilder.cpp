//
// Created by lhumphreys on 10/05/2020.
//

#include "PreParamConfigBuilder.h"

namespace  {
    constexpr const char* const defaultContent = R"CONFIG(
[Output every realisation]
1

[Output bitmap]
0

[Output incidence by administrative unit]
0

[Output infection tree]
0

==========================================================

[Include administrative units within countries]
1

[Equilibriation time]
0

[Grid size]
0.075

[Spatial domain for simulation]
73	6.3
136	54

[Initial immunity profile by age]
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0

[Initial immunity applied to all household members]
1

[Relative spatial contact rates by age]
0.6	0.7	0.75	1	1	1	1	1	1	1	1	1	1	1	1	0.75	0.5
(POLYMOD, averaging 20-70)

[Household attack rate]
0.1
(Adjusted to be the same as Cauchemez 2004 for R0=1.3.)

[Household transmission denominator power]
0.8
(Cauchemez 2004)

[Relative transmission rates for place types]
0.14	0.14	0.1	0.07
(School=2 x workplace. This gives Longini AJE 1988 age-specific infection attack rates for R0=1.3.
Also comparable with 1957 pandemic attack rates from Chin.)

[Proportion of between group place links]
0.25	0.25	0.25	0.25
(25% of within-group contacts)

[Include symptoms]
1

[Delay from end of latent period to start of symptoms]
0.5
(assume average time to symptom onset is a day)

[Proportion symptomatic by age group]
0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66 0.66

[Symptomatic infectiousness relative to asymptomatic]
1.5

[Relative rate of random contacts if symptomatic]
0.5

[Relative level of place attendance if symptomatic]
0.25 	0.25	0.5 	0.5

[Model symptomatic withdrawal to home as true absenteeism]
1

[Maximum age of child at home for whom one adult also stays at home]
16

[Proportion of children at home for whom one adult also stays at home]
1

[Duration of place absenteeism for cases who withdraw]
7

[Place close round household]
1

[Absenteeism place closure]
0

#[Max absent time]
#0
#Not used because [Absenteeism Place Closure] is 0.

[Initial number of infecteds]
1000

[Time when infection rate changes]
30

[Initial rate of importation of infections]
0

[Changed rate of importation of infections]
0

[Length of importation time profile provided]
0

[Daily importation time profile]
0.00039637	0.000422404	0.000603232	0.000806818	0.000977838	0.001215654	0.001475435	0.001759331	0.002095855	0.002476933	0.002909161	0.003410198	0.003982451	0.004638805	0.005395127	0.00626298	0.007261369	0.008410463	0.009732184	0.011253768	0.01300553	0.015022328	0.017344927	0.020019826	0.023100555	0.026649391	0.030737285	0.035446471	0.04087166	0.04712199	0.054323081	0.062619805	0.072178958	0.083192875	0.095883242	0.110505088	0.127353055	0.146765647	0.169134051	0.194907414	0.224605405	0.258825037	0.298255169	0.343688393	0.396040694	0.456363956	0.525872339	0.605965353	0.698253328	0.804594637	0.927128729	1.068321589	1.231009953	1.418469229	1.634476217	1.883366252	2.170149943	2.500595049	2.881346836	3.320054954	3.825541988	4.407960394	5.07901906	5.852193458	6.742999237	7.769281222	8.951656384	10.31379847	11.88295306	13.690484	15.7725322	18.17054397	20.93225706	24.11247717	27.77414928	31.98955641	36.84153527	42.42484495	48.84810841	56.23529325	64.72777172	74.48650501	85.69401624	98.55689323	113.307934	130.2079818	149.5482524	171.650606	196.8670786	225.5805289	258.1996665	295.1479906	336.8602628	383.7567184	436.226154	494.5852818	559.0401758	629.6271715	706.1466306	788.0877032	874.5385994	964.1277368	1054.942274	1144.497997	1229.819016	1307.478109	1373.849859	1425.375658	1458.909049	1472.112189	1463.74025	1433.873478	1383.937547	1316.559006	1235.24025	1143.978092	1046.827852	947.5742692	849.4524822	755.0099762	666.1067926	583.9342875	509.1260534	441.8703774	382.0284161	329.2333209	282.9819783	242.6943429	207.7671547	177.6025491	151.6341438	129.3333359	110.223406	93.87499488	79.90856345	67.99027638	57.82900897	49.17215405	41.80131863	35.5286855	30.19272742	25.65482116	21.79680064	18.51741927	15.73036742	13.3620726	11.34984238	9.640307581	8.188006869	6.954337378	5.906435165	5.016354116	4.260368274	3.61826508	3.072912654	2.609742089	2.216371142	1.882286966	1.598554546	1.357591285	1.152944119	0.979149081	0.831549648	0.70620165	0.59974816	0.509342763	0.43256591	0.367362791	0.311990061	0.264964778	0.22502858	0.19111364	0.162311178	0.137852214	0.117080312	0.099440002	0.084459683	0.07173828	0.06093513	0.051761119

[Reproduction number]
2

[Power of scaling of spatial R0 with density]
0

[Include latent period]
1

[Latent period]
4.59
(From Marc's estimates) - minus half a day to account for infectiousness pre symptom onset

[Latent period inverse CDF]
0	0.098616903	0.171170649	0.239705594	0.307516598	0.376194441	0.446827262	0.520343677	0.597665592	0.679808341	0.767974922	0.863671993	0.968878064	1.086313899	1.219915022	1.37573215	1.563841395	1.803041398	2.135346254	2.694118208	3.964172493
(From Marc's estimates)

[Model time varying infectiousness]
1

[Infectiousness profile]
0.487464241	1	1.229764827	1.312453175	1.307955665	1.251658756	1.166040358	1.065716869	0.960199498	0.855580145	0.755628835	0.662534099	0.577412896	0.500665739	0.432225141	0.371729322	0.318643018	0.272340645	0.232162632	0.19745264	0.167581252	0.141960133	0.120049578	0.101361532	0.085459603	0.071957123	0.060514046	0.050833195	0.04265624	0.035759641	0.029950735	0.025064045	0.02095788	0.017511251	0.014621091	0.012199802	0.010173075	0.008477992	0.007061366	0.005878301	0.00489096	0.004067488	0.003381102	0.00280931	0.002333237	0.001937064	0.001607543	0.001333589	0.001105933	0.00091683	0.000759816	0.000629496	0.000521372	0.000431695	0.000357344	0.000295719	0.000244659

[Infectious period]
14

[Infectious period inverse CDF]
0	0.171566836	0.424943468	0.464725594	0.50866631	0.55773764	0.613298069	0.67732916	0.752886568	0.843151261	0.895791527	0.955973422	1.026225109	1.110607115	1.216272375	1.336349102	1.487791911	1.701882384	1.865779085	2.126940581	2.524164972
(Cauchemez)

[k of individual variation in infectiousness]
1

==========================================================

[Use global triggers for interventions]
1

[Use admin unit triggers for interventions]
0

[Number of sampling intervals over which cumulative incidence measured for global trigger]
1000

[Use cases per thousand threshold for area controls]
0

[Divisor for per-capita global threshold (default 1000)]
100000

[Divisor for per-capita area threshold (default 1000)]
1000

[Trigger alert on deaths]
1

[Number of deaths accummulated before alert]
10000

[Number of days to accummulate cases/deaths before alert]
100

[Day of year trigger is reached]
100

[Alert trigger starts after interventions]
1

[Day of year interventions start]
76

[Proportion of cases detected for treatment]
1

[Treatment trigger incidence per cell]
100000

[Places close only once]
0

[Social distancing only once]
1

[Use ICU case triggers for interventions]
1

[Proportion of cases detected before outbreak alert]
1

[Number of detected cases needed before outbreak alert triggered]
0

====================================

[Do one generation]
0

[Bitmap scale]
60

[Bitmap y:x aspect scaling]
1.5

[Calculate spatial correlations]
0

[Bitmap movie frame interval]
300

[Record infection events]
0

[Record infection events per run]
0

[Max number of infection events to record]
10000000000

[Limit number of infections]
0

[Max number of infections]
10000000000

===================================

[Do Severity Analysis]
1

[Mean_MildToRecovery]
7

[Mean_ILIToRecovery]
7

[Mean_ILIToSARI]
5

[Mean_SARIToRecovery]
1

[Mean_SARIToDeath]
1

[Mean_SARIToCritical]
1

[Mean_CriticalToCritRecov]
1

[Mean_CriticalToDeath]
1

[Mean_CritRecovToRecov]
1

[MeanTimeToTest]
4

[MeanTimeToTestOffset]
1

[MeanTimeToTestCriticalOffset]
3.3

[MeanTimeToTestCritRecovOffset]
9.32

[MildToRecovery_icdf]
0	0.341579599	0.436192391	0.509774887	0.574196702	0.633830053	0.690927761	0.74691114	0.802830695	0.859578883	0.918015187	0.97906363	1.043815683	1.113669859	1.190557274	1.277356871	1.378761429	1.50338422	1.670195767	1.938414132	2.511279379

[ILIToRecovery_icdf]
0	0.341579599	0.436192391	0.509774887	0.574196702	0.633830053	0.690927761	0.74691114	0.802830695	0.859578883	0.918015187	0.97906363	1.043815683	1.113669859	1.190557274	1.277356871	1.378761429	1.50338422	1.670195767	1.938414132	2.511279379

[ILIToSARI_icdf]
0	0.341579599	0.436192391	0.509774887	0.574196702	0.633830053	0.690927761	0.74691114	0.802830695	0.859578883	0.918015187	0.97906363	1.043815683	1.113669859	1.190557274	1.277356871	1.378761429	1.50338422	1.670195767	1.938414132	2.511279379

[SARIToRecovery_icdf]
0	0.634736097	1.217461548	1.805695261	2.41206761	3.044551205	3.71010552	4.415905623	5.170067405	5.982314035	6.864787504	7.833196704	8.908589322	10.12027655	11.51100029	13.14682956	15.13821107	17.69183155	21.27093904	27.35083955	41.35442157

[SARIToDeath_icdf]
0	1.703470233	2.39742257	2.970367222	3.491567676	3.988046604	4.474541783	4.960985883	5.455292802	5.964726999	6.496796075	7.06004732	7.665014091	8.325595834	9.061367792	9.901900127	10.8958347	12.133068	13.81280888	16.56124574	22.5803431

[SARIToCritical_icdf]
0	0.108407687	0.220267228	0.337653773	0.46159365	0.593106462	0.733343356	0.88367093	1.045760001	1.221701998	1.414175806	1.62669998	1.864032461	2.132837436	2.442868902	2.809242289	3.257272257	3.834402667	4.647120033	6.035113821	9.253953212

[CriticalToCritRecov_icdf]
0	1.308310071	1.87022015	2.338694632	2.76749788	3.177830401	3.581381361	3.986127838	4.398512135	4.824525291	5.270427517	5.743406075	6.252370864	6.809125902	7.430338867	8.141231404	8.983341913	10.03350866	11.46214198	13.80540164	18.95469153

[CriticalToDeath_icdf]
0	1.60649128	2.291051747	2.860938008	3.382077741	3.880425012	4.37026577	4.861330415	5.361460943	5.877935626	6.4183471	6.991401405	7.607881726	8.282065409	9.034104744	9.894486491	10.91341144	12.18372915	13.9113346	16.74394356	22.96541429

[CritRecovToRecov_icdf]
0	0.133993315	0.265922775	0.402188416	0.544657341	0.694774487	0.853984373	1.023901078	1.206436504	1.403942719	1.619402771	1.856711876	2.121118605	2.419957988	2.763950408	3.169692564	3.664959893	4.301777536	5.196849239	6.7222126	10.24997697

[Prop_Mild_ByAge]
0.666244874	0.666307235	0.666002907	0.665309462	0.663636419	0.660834577	0.657465236	0.65343285	0.650261465	0.64478501	0.633943755	0.625619329	0.609080537	0.600364976	0.5838608	0.566553872	0.564646465

[Prop_ILI_ByAge]
0.333122437	0.333153617	0.333001453	0.332654731	0.33181821	0.330417289	0.328732618	0.326716425	0.325130732	0.322392505	0.316971878	0.312809664	0.304540269	0.300182488	0.2919304	0.283276936	0.282323232

[Prop_SARI_ByAge]
0.000557744	0.000475283	0.000877703	0.001794658	0.004006955	0.007711884	0.012167229	0.017359248	0.021140307	0.027047193	0.03708932	0.039871236	0.040788928	0.027444452	0.101605674	0.142001415	0.150469697

[Prop_Critical_ByAge]
7.49444E-05	6.38641E-05	0.000117937	0.000241149	0.000538417	0.00103625	0.001634918	0.002491477	0.003467496	0.005775292	0.011995047	0.021699771	0.045590266	0.072008084	0.022603126	0.008167778	0.002560606

[CFR_Critical_ByAge]
0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896	0.5234896

[CFR_SARI_ByAge]
0.125893251	0.12261338	0.135672867	0.152667869	0.174303077	0.194187895	0.209361731	0.224432564	0.237013516	0.257828065	0.290874602	0.320763971	0.362563751	0.390965457	0.421151485	0.447545892	0.482

[CFR_ILI_ByAge]
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0

[Mean_ILIToDeath]
7

[ILIToDeath_icdf]
0	2.257735908	3.171065856	3.924183798	4.608738224	5.260437017	5.898728066	6.53669783	7.184755068	7.852438367	8.549591424	9.287408763	10.07967529	10.94457146	11.90769274	13.00769447	14.3081531	15.92655201	18.12320384	21.71626849	29.58154704


[Mean child age gap]
2

[Min adult age]
19

[Max MF partner age gap]
5

[Max FM partner age gap]
5

[Min parent age gap]
19

[Max parent age gap]
44

[Max child age]
20

[One Child Two Pers Prob]
0.08

[Two Child Three Pers Prob]
0.11

[One Pers House Prob Old]
0.5

[Two Pers House Prob Old]
0.5

[One Pers House Prob Young]
0.23

[Two Pers House Prob Young]
0.23

[One Child Prob Youngest Child Under Five]
0.5

[Two Children Prob Youngest Under Five]
0.0

[Prob Youngest Child Under Five]
0

[Zero Child Three Pers Prob]
0.25

[One Child Four Pers Prob]
0.2

[Young And Single Slope]
0.7

[Young And Single]
36

[No Child Pers Age]
44

[Old Pers Age]
60

[Three Child Five Pers Prob]
0.5

[Older Gen Gap]
19
)CONFIG";
}

std::unique_ptr<ConfigFile> PreParamConfigBuilder::BuildConfig(const std::string &fname) {
    std::stringstream buf;
    buf << defaultContent << std::endl;
    const auto addItem = [&] (const std::string& name, const std::optional<std::string>& val) {
        if (val.has_value()) {
            buf << std::endl;
            buf << "[" << name << "]" << std::endl;
            buf << val.value() << std::endl;
        }
    };
    addItem("Update timestep", updateTimestep);
    addItem("Sampling timestep", samplingTimestep);
    addItem("Sampling time", samplingTotalTime);

    addItem("Number of realisations", numberOfRealisations);
    addItem("Number of non-extinct realisations", numberOfNonExtinctRealisations);
    addItem("Only output non-extinct realisations", onlyOutputNonExtinctRealisations);

    addItem("Maximum number of cases defining small outbreak", maxNumForSmallOutbreak);

    addItem("Number of micro-cells per spatial cell width", numMicroCellsPerSpatialCell);

    addItem("OutputAge", outputAge);
    addItem("OutputSeverityAdminUnit", outputSeverityAdminUnit);
    addItem("OutputR0", outputR0);
    addItem("OutputControls", outputControls);
    addItem("OutputCountry", outputCountry);
    addItem("OutputAdUnitVar", outputAdUnitVar);
    addItem("OutputHousehold", outputHousehold);
    addItem("OutputInfType", outputInfType);
    addItem("OutputNonSeverity", outputNonSeverity);
    addItem("OutputNonSummaryResults", outputNonSummaryResults);

    return std::make_unique<ConfigFile>(fname, buf.str());
}
