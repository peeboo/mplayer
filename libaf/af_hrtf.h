/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPLAYER_AF_HRTF_H
#define MPLAYER_AF_HRTF_H

#define HRTF_MIX_51 0
#define HRTF_MIX_STEREO 1
#define HRTF_MIX_MATRIX2CH 2

/* Amplitude scaling factors */
#define M17_0DB		0.1414213562
#define M9_03DB		0.3535533906
#define M6_99DB		0.4472135955
#define M4_77DB		0.5773502692
#define M3_01DB		0.7071067812
#define M1_76DB		0.8164965809

#define DELAYBUFLEN	1024	/* Length of the delay buffer */
#define HRTFFILTLEN	64	/* HRTF filter length */
#define IRTHRESH	0.001	/* Impulse response pruning thresh. */

#define AMPLNORM	M6_99DB	/* Overall amplitude renormalization */

#define BASSFILTFREQ	180	/* Bass compensation filter cut (Hz) */
#define BASSFILTLEN	193	/* Bass compensation filter length */
#define BASSGAIN	M_SQRT2	/* Bass compensation gain */
#define BASSCROSS	0.35	/* Bass cross talk */

#define FWRDURATION	240	/* FWR average duration (samples) */
#define MATREARDELAY	720	/* Matrix mode rear delay (samples) */

#define MATAGCTRIG	8.0	/* (Fuzzy) AGC trigger */
#define MATAGCDECAY	1.0	/* AGC baseline decay rate (1/samp.) */
#define MATAGCLOCK	0.2	/* AGC range (around 1) where the
				   matrix behaves passively */
#define MATCOMPGAIN	0.37	/* Cross talk compensation gain,
				   0.50 - 0.55 is full cancellation. */

#define CFECHODELAY	360	/* Center front echo delay (samples) */
#define CFECHOAMPL	M17_0DB	/* Center front echo amplitude */

#define STEXPAND2	0.07	/* Stereo expansion / 2 */

/* Head related impulse response (HRIR) derived from KEMAR measurement
   data by Bill Gardner <billg@media.mit.edu> and Keith Martin
   <kdm@media.mit.edu>

   URL: http://sound.media.mit.edu/KEMAR.html

   Distributed under GPL with authors' permission
*/

/* EQUALIZED KEMAR HRIR

How to generate these data:

1. You need the MIT Media Lab's KEMAR data, read it into an software
   capable of signal/time series analysis (like Mathematica, Matlab,
   ...)

2. Construct an equalizing FIR inverse filter by calculating the
   transfer function of the front, same side impulse response, then
   take 1 over the absolute magnitude.

3. Cut the poles in the inverse filter's transfer function
   specification by limiting the amplification to 2.5 (note, this
   number assumes that you have correct signal processing
   normalization of the Fourier transform).

4. Design the FIR inverse filter by calculating the inverse Fourier
   transform, then chopping the coefficients down to a reasonable
   number (N = 15 is used here), apply the Kaiser-Bessel window (alpha
   = 2 is used here).  Note the objective is remove the color bias
   only (as if you are using an equalizer), _not_ to do a full inverse
   filtering. (Note: beta = pi*alpha in other notation.)

   For N = 15, alpha = 2, you should get the following impulse
   response:

    0.001001558668605168,  0.00698457265741865,  0.040453643039829436,
    0.012230541722147855, -0.11939760844854072,  0.16468099899755967,
   -0.30297563073747436,   1.3140211791355982,  -0.30297563073747436,
    0.16468099899755967,  -0.11939760844854072,  0.012230541722147855,
    0.040453643039829436,  0.00698457265741865,  0.001001558668605168

5. Linearly convolve all KEMAR HRIR with this inverse filter.

6. Resample from 44.1 kHz sampling frequency to 48 kHz.
*/

/* Center front (-5 degree) - not 0 degree in order to create a clear
   front image from a finite distance */
static const float cf_filt[128] = {
   -0.00008638082319075036, 0.0003198059946385229,
   -0.0005010631339162132, 0.0011424741331126876,
   -0.001584220794688753, 0.001742715363246275,
   -0.0011080796626780694, 0.0001651829990860167,
   0.005235028337314985, 0.0035223828473357776,
   0.010057681388431303, -0.033469432129545514,
   0.013391253316233523, 0.004858462839827063,
   0.08172161220103627, 0.26158596134500023,
   -0.12420314583323326, -0.14298458356097565,
   0.14421897280453896, -0.1635792507629016,
   -0.02187136722480014, 0.2426863044711817,
   0.07229814207917194, 0.0942742651913879,
   0.29856830878076834, 0.2944146162057754,
   -0.12122157003421209, -0.19640092165631157,
   0.11623836502034968, -0.05794027397995521,
   -0.34313138341973776, -0.19487516249168105,
   0.010118993953802401, -0.09460218797710966,
   -0.16761521117359582, 0.004154461610153861,
   0.052768641758969316, -0.00041823982226147407,
   0.021634960445143514, 0.07562793486871108,
   0.08895407129506479, 0.039857755093416214,
   0.044257936180422945, 0.061557584906101664,
   0.015547268541895703, -0.023908191934932484,
   0.009498030443468223, 0.03816269003221337,
   -0.009820500607303615, -0.042003975527908084,
   -0.03335447117311547, -0.029294510859746596,
   -0.05212623136198511, -0.073427547153205,
   -0.061190797824958836, -0.04620925059966413,
   -0.04204619420702159, -0.02331915902615157,
   0.00211481411477094, 0.00852563995740107,
   0.008766809731743399, 0.008666632180812078,
   0.018279202191625352, 0.02924332751289675,
   0.022293148257836494, 0.012362146008584188,
   0.008572582458807008, 0.006491370763597344,
   -0.0019366944997535774, -0.006318669309634434,
   -0.006457921690218669, -0.015050265524669974,
   -0.02110660282616213, -0.017027809096377904,
   -0.01651052305334348, -0.022770064150046673,
   -0.01999875754219472, -0.012294792027337775,
   -0.011506057031057188, -0.011448970577312903,
   -0.004823572302580925, 0.0022451134042777883,
   0.004145473526859826, 0.005629030064546135,
   0.008588029213398785, 0.010092048834844231,
   0.007182013245552008, 0.0014600979508720656,
   -0.0038314646272511756, -0.003443901997881347,
   -0.0029483418254804047, -0.007609357112679647,
   -0.006518368948030822, -0.004495803701497202,
   -0.007109113004849672, -0.008346237278084265,
   -0.005560847336252453, -0.002993453167553188,
   -0.005122897816824269, -0.004389782626604215,
   -0.0010912633695218108, -0.0019712029474458835,
   -0.005870162265802235, -0.005626159534954128,
   -0.00027254977910844407, 0.0013794425431633785,
   -0.0005919083190430062, -0.0007861203545416682,
   -0.0007049560240893946, -0.0032720188494468868,
   -0.004460645567968504, -0.0032018528193571696,
   -0.0030579229375062105, -0.003593998902656612,
   -0.0038032977997776445, -0.004613776010454773,
   -0.0059796549143736845, -0.00420126194319768,
   -0.0012374419948287222, 0.0008572699213050608,
   0.0021490971020081094, 0.00047295283198381995,
   -0.0009670277915884887, -0.001354440866080231,
   -0.002962902746547851, -0.00533935813338141,
   -0.005469203016468759, -0.004355784273189485
};
/* Front,   same side (30 degree) */
static const float af_filt[128] = {
   -0.004140580614755493, 0.005790934614385445,
   0.003318916682081112, 0.014257145544366063,
   0.007328442487127339, -0.06550381777876194,
   0.03502225818161845, -0.013090579770708259,
   0.2517776798694195, 0.420770489950659,
   -0.3418854608834852, -0.24371032493696737,
   0.04901356150030018, -0.1778083521632833,
   0.26448004245714163, 0.23245199964546834,
   0.033053145803936305, 0.46811222821062415,
   0.5359265986255611, -0.011912195468533787,
   -0.39763432601411647, -0.034482864386898314,
   0.029445398240649626, -0.3850940407863262,
   -0.3272328478175581, -0.14701421403616477,
   -0.08522137400169517, -0.14936851633336035,
   -0.09432605283433723, 0.0991200405937827,
   0.011075012089917331, -0.0051036489980274685,
   0.0933903289749412, 0.1344189369609565,
   0.10507466913017807, 0.04240159324684365,
   0.06559270110638656, 0.026984119875617524,
   -0.03359846103238096, -0.018000197099174275,
   0.042031818548178244, 0.03849039666888434,
   -0.02450829674011345, -0.03407882403088576,
   -0.029230189282961977, -0.046964865291761734,
   -0.09458258700116245, -0.1527349330901158,
   -0.15411577687826097, -0.08761679790956928,
   -0.033623549089171874, -0.007204768531481949,
   0.008273425020444852, 0.021368717994908505,
   0.04366608267875025, 0.05660907333076205,
   0.06775726495503939, 0.05621881735271431,
   0.03576231950669927, 0.02500825834889175,
   0.015423811076054601, 0.007903258334503761,
   -0.0053873014137761945, -0.006987955469434698,
   -0.012027972007598602, -0.025228281243816594,
   -0.026225091797257318, -0.023809293997344882,
   -0.03250172017712295, -0.03195696301067249,
   -0.01784813952189948, -0.01663267233760342,
   -0.016184530450468065, -0.011659883749357463,
   -0.0035378511240219163, -0.0005485800790443406,
   0.0018432660108168625, 0.011634844139907534,
   0.018333603402051105, 0.020447379185133056,
   0.00850783664147828, 0.0004694148911037838,
   -0.0017047130409786676, -0.0022409152834483997,
   -0.000860472174892845, -0.004111075059198666,
   -0.003527843382056666, -0.009640160874903018,
   -0.01750044574231376, -0.015613389403672443,
   -0.010790028120953001, -0.0095313499955768,
   -0.007469721416726809, -0.0019186578145117315,
   -0.00014977322572890802, -0.0029803838028179728,
   -0.006520567233727221, 0.000035015132033882596,
   0.009245098100543752, 0.009896930052308656,
   0.008316744929565786, 0.004575207140193997,
   -0.0000647420103997081, -0.004502916832871627,
   -0.004225962213251224, -0.002886014126381486,
   -0.006416834142585976, -0.007156609995423569,
   -0.008840274447579472, -0.01441763751386817,
   -0.015435817484659574, -0.00924487254924743,
   -0.0021571721940235205, 0.0028540722992305453,
   0.00273577475088536, -0.000788412365513805,
   -0.0032650029728365907, -0.003880217646231338,
   -0.0035302087299613778, -0.0038531436176586246,
   -0.0011921632190514074, -0.0020722967099011938,
   -0.004985351145629344, -0.0042375588844648735,
   -0.003030360463006021, -0.0014161075428041471,
   -0.0005083025643192044, 0.00035096963769606926
};
/* Front,   opposite (-30 degree) */
static const float of_filt[128] = {
   -0.000013472538374193126, -0.00008048061877079751,
   0.000043927265781258155, -0.000017931700794858892,
   -0.000034774602476112886, -0.00009576223008735474,
   0.0001557797638630691, -0.00018742885883751094,
   0.00026512448626705716, -0.0001451040203319678,
   -0.00008263233117758043, 0.0006486245853639179,
   -0.0010631408451846698, 0.0026571994100746143,
   0.0014179177997092787, 0.0062326502956616256,
   -0.008194149324545333, -0.006568029415878379,
   0.009538759710818582, 0.012309193558632693,
   0.12336638055838955, 0.046164307101829005,
   -0.10228706407884815, 0.04047687260345798,
   -0.00296595313977046, -0.07057949208414134,
   0.08172114840714612, 0.08736490764127891,
   0.05105250431333021, 0.11627179512747428,
   0.20717888490340705, 0.09375052213570291,
   -0.09784374168330194, -0.010493571845901443,
   0.053131894303891716, -0.10157443971694806,
   -0.16264032634244974, -0.05402369511361273,
   -0.0274403608654217, -0.09860277022495063,
   -0.06841875821090282, -0.004434574400066223,
   -0.0005222661652743502, -0.006231881259827263,
   0.014410397820340159, 0.04885649512730243,
   0.04361962569042684, 0.03399214029009391,
   0.04961073933475931, 0.04067325604132289,
   0.007850647519227257, 0.004564440466905299,
   0.02257107958021618, 0.008183791928884486,
   -0.014913479343180557, -0.018685938460856224,
   -0.01745737397226911, -0.02327177054233603,
   -0.03723048632685227, -0.044739390162299685,
   -0.042651220125613766, -0.03730017561004743,
   -0.029039465434276192, -0.01885087458914294,
   -0.01207127752277769, -0.006779800724164512,
   -0.001930416967444157, 0.000029454577995528385,
   0.0013822760965755472, 0.0014799128583230202,
   0.0002068200609199832, 0.0022254295286201083,
   0.005143858159434566, 0.0018580542060917013,
   -0.0019426046325146259, -0.0014464042108543495,
   -0.0034430083560735582, -0.009692758426099499,
   -0.011840035292593485, -0.010716508855893968,
   -0.012939889036853034, -0.0121846427935653,
   -0.006198503315630782, -0.0023186723099380305,
   -0.002679872498314837, -0.003086020446226295,
   -0.0015709623347698936, -0.0008147490468332398,
   -0.0012384575726770983, -0.0005212877089109362,
   0.0017707578744906142, 0.001324932723905786,
   -0.0017023653780617696, -0.0045108927752919425,
   -0.005422155613096912, -0.0039489323837623835,
   -0.005295995750506547, -0.00629706566356189,
   -0.004685732198036754, -0.0048076735568143,
   -0.005978864279217503, -0.005928999306332966,
   -0.004187703549017582, -0.003213999896976475,
   -0.0028068699816073414, -0.0010889703907593833,
   0.0003276714243495386, -0.0013015007040186994,
   -0.003208050402434782, -0.0025115319088208545,
   -0.0013787553006401076, -0.0018279087370218635,
   -0.0025904836507747754, -0.002071221947222004,
   -0.0026424212922485594, -0.0039837031817577,
   -0.0041635566057380965, -0.004355223489150822,
   -0.004350395332709937, -0.0036693292471930263,
   -0.003386384394185026, -0.003972568655001128,
   -0.004332336840023821, -0.002648767912111827,
   -0.001384410080218114, -0.0011353792711849466,
   -0.0013726264946164232, -0.0020075119315034313
};
/* Rear,   same side (135 degree) */
static const float ar_filt[128] = {
   0.004573315040810066, 0.0013592578059426913,
   0.01553271930902704, -0.0002356117224941317,
   -0.05746098219774702, 0.03430688963370445,
   0.00808371687447385, 0.21893535841158596,
   0.2984357591724814, -0.3302799746504719,
   -0.3194029149806245, 0.21633225051331056,
   0.24371260938097083, -0.08843705549751085,
   0.03939684701343366, 0.45386926431114494,
   0.07599118140753386, -0.18114706160474578,
   0.285640624686038, 0.4049515236666218,
   -0.05347890222071792, -0.31464359045319074,
   -0.1033502246468194, -0.04553593949283157,
   -0.1880747731157464, -0.13629090230626037,
   -0.10435789106123239, -0.19818232801888755,
   -0.16701805476330397, -0.022793111199284,
   0.058049696762683685, 0.007048321372693906,
   -0.002966419183225961, 0.10140569697797763,
   0.11648999956673124, 0.05218347182779882,
   0.028427001212735392, 0.04151900310166159,
   -0.0006960604221423734, -0.05898623212226975,
   -0.03801934531173312, -0.029306970535287986,
   -0.04549125782835908, -0.0599222718506552,
   -0.058299618975430116, -0.03765579129720727,
   -0.03559302657499581, -0.020647901025903054,
   -0.005720957338744348, -0.0041915732688915545,
   -0.0011470880098346143, 0.008737404798553,
   0.023444168098121512, 0.024204226042172663,
   0.01894897166475026, 0.020807655257479588,
   0.021570431128040954, 0.006800556178576289,
   -0.009000089216921362, -0.010969824547067934,
   -0.0033653428332822374, -0.012676936164668659,
   -0.026739938673413587, -0.023427869194287573,
   -0.023302007105117244, -0.023647155590533712,
   -0.021289317515613106, -0.009120487305069884,
   0.0009251551667728967, 0.00004285344125653763,
   -0.00009042365479456271, 0.00022573242339446494,
   0.00720168491586098, 0.007111875505402431,
   0.003186514817683482, 0.00810087718334745,
   0.012619557025922575, 0.007854726400013397,
   -0.0024013592881066267, -0.001452457473161119,
   -0.0025535188366093945, -0.012428911627809337,
   -0.013729251536694145, -0.0070099675146427344,
   -0.007165284278706593, -0.01639289295622301,
   -0.015831795079778305, -0.007305768485523729,
   -0.003608863157004021, -0.0032640528878698084,
   0.0030901263998481944, 0.00749497566124848,
   0.002515185532327241, 0.00004840875738621367,
   0.0017596043486043966, 0.0046229941553338144,
   0.0034259167322926096, 0.003707347634186093,
   0.0035584806528586328, -0.0019078936035275198,
   -0.006057343815214898, -0.0069262470468817,
   -0.004345020728618624, -0.004177623355574794,
   -0.005373506556122508, -0.006624933928893836,
   -0.008679541408588839, -0.010718719681595322,
   -0.011392246979594496, -0.007893917064389902,
   -0.0027572935365832536, -0.00006064707149834412,
   -0.0012512537319656323, -0.0024501501002409786,
   -0.0022106788572895998, -0.00234124933370301,
   -0.0008953445167066823, 0.0005393670625637734,
   -0.00033175600142209297, -0.004023994309351289,
   -0.008655472335784443, -0.009899957354849682,
   -0.008664952919996412, -0.00553483124503576,
   -0.003735336089277662, -0.002754824348643885,
   -0.0026884314856593368, -0.004084181815125924
};
/* Rear,   opposite (-135 degree) */
static const float or_filt[128] = {
   0.0001220944028243897, -0.000021785381808441314,
   5.823057988603169e-6, -0.00001217768176447613,
   -0.00006123604397345513, 5.574117262531134e-6,
   -0.00004935331914366778, 1.1771577934768211e-6,
   -0.000059236211621095756, 9.503536190497286e-6,
   -0.0001494445696103564, 0.00012248858284145305,
   -0.0000963975321456313, 6.017905197665205e-6,
   0.00003353395360402643, -0.0001931511015359506,
   0.0005113536523931485, -0.0005676652619386114,
   0.0012057159755477467, 0.0009370492250339692,
   0.004596472288877981, -0.0018831773384237068,
   -0.008208535225621212, 0.0038178646400751056,
   0.008726517739105965, 0.06664363898418262,
   0.06788684221502142, -0.04492315162807267,
   -0.04019906311255255, 0.026203059677375153,
   0.013678129114847544, -0.014334962223993527,
   0.010141709596167392, 0.11559131576945537,
   0.1586402064538425, 0.059975334707967023,
   0.004671725963777715, 0.031498678282775874,
   0.014338626006524587, -0.014749719448472231,
   -0.02055508237941379, -0.05407690143992048,
   -0.07767559836886143, -0.05029091786216801,
   -0.030808335706574427, -0.03401958135442541,
   -0.030520368430288967, -0.014168302104259355,
   0.011907621259989802, 0.014286081013069,
   0.006377467879613449, 0.018546823568277478,
   0.028297012771618273, 0.025222339408338186,
   0.021931611353415138, 0.019708894333646355,
   0.01729258494072014, 0.017468204169564034,
   0.009729094845051928, -0.002976992018531901,
   -0.00956986166277019, -0.016125733548332074,
   -0.02934094241442545, -0.04133767871051455,
   -0.043536981145416466, -0.0385966307108608,
   -0.02784453599342459, -0.018995135307247116,
   -0.012849534096536747, -0.004437491064613308,
   0.00028385411598204655, 0.003776874988516643,
   0.008069432041547833, 0.008764754183751848,
   0.008020908861878062, 0.006830351461360802,
   0.002218330884267235, -0.0020478725582339444,
   -0.003997428121462543, -0.007066287373515421,
   -0.00940847412544698, -0.010938998446237963,
   -0.011775483016151306, -0.011391103919484287,
   -0.010586061195163017, -0.009842793078929053,
   -0.007753202010139829, -0.00569213732353025,
   -0.006506783349722073, -0.005346134281903736,
   -0.003913089814898934, -0.0036091443854759727,
   -0.0020328564301266287, 0.00017932870773467683,
   0.0032779786679056357, 0.003969695813293966,
   0.0020339334412434987, -0.00011345940675415259,
   -0.0018344103399567666, -0.003556764701666365,
   -0.004263523639408391, -0.002940568582022133,
   -0.0034341188272627556, -0.006023399920020824,
   -0.0077456903203677865, -0.007912219312377842,
   -0.00625202770436523, -0.00530785086116117,
   -0.005569722659634311, -0.004664448462594344,
   -0.0037747773914077747, -0.004175649656985592,
   -0.004659601521384289, -0.005008602967819641,
   -0.004730625079902729, -0.0034039554356604146,
   -0.0017110333873406587, -0.0006091938771510242,
   -0.0016051679050678297, -0.003312864664007262,
   -0.004505512715977288, -0.004152222189861692,
   -0.003218596419678823, -0.0027277806209877343,
   -0.001715005444317267, -0.0012589960071233749,
   -0.001852908777923165, -0.002540339553144362
};
/* Center rear (180 degree) */
static const float cr_filt[128] = {
   -0.00005989110716536726, -0.00022790291829128702,
   0.0002659166098971966, -0.0003774772716776257,
   0.0004540309551867803, -0.000420238187386368,
   0.00025518536450885686, 0.00028285526288953955,
   -0.001016391007574093, 0.0028634984299063795,
   0.0021574799687976045, 0.01035121276682072,
   -0.010481720917298163, -0.013197198495899292,
   0.0031928225328717195, 0.02903137843618603,
   0.1632429772511569, 0.1047487989875262,
   -0.10464685060623742, -0.09260196288035998,
   -0.007514241993554443, 0.013596249226741712,
   -0.019876166508450258, 0.1255626123599804,
   0.3648170359521724, 0.19458249753223478,
   -0.04434070930031298, 0.046582528121935265,
   0.09484427347230277, -0.03137795311969644,
   -0.10297437925363695, -0.09351091015917065,
   -0.1129521092162064, -0.14925322995658827,
   -0.1231466295584665, -0.06356719756705227,
   -0.05442277895126282, -0.07568433015661316,
   -0.023314932828602003, 0.04260950721318558,
   0.02249026315598923, 0.02048195669571197,
   0.05651342117268278, 0.05885038917623213,
   0.03797102097397795, 0.011767394419953451,
   0.00560502503429481, 0.005051125343961189,
   -0.012925933188033823, -0.023918884651306566,
   -0.013251659441678816, -0.010694772488866284,
   -0.03080486448617846, -0.03661278237783158,
   -0.0379227303416262, -0.042189005718490775,
   -0.026595666344596286, -0.009759025956801257,
   -0.002064986663513004, -0.002420117028098389,
   -0.006629991977552491, 0.004619970897631026,
   0.019450642967537877, 0.0173521119057514,
   0.017641425439988062, 0.02270029598048491,
   0.018976431925275348, 0.009299852902290885,
   -0.001695039371619912, -0.00675162574265618,
   -0.009380968871003034, -0.011208396125485165,
   -0.01308640049201482, -0.0165636375633249,
   -0.022004099870933345, -0.025173458684139286,
   -0.016918759559175375, -0.00865150653575917,
   -0.006999929082792643, -0.005454830010518988,
   -0.0021129521131095317, 0.00018717090054046307,
   -0.0002864344788569993, 0.0017615225381095569,
   0.006985907557802283, 0.010577308310476465,
   0.006466104789306027, -0.0014988738575948326,
   -0.0039669755229277195, -0.0065156971200080235,
   -0.009343206924192169, -0.0076430644693577495,
   -0.004395214976600924, -0.003052735340422483,
   -0.007019103043066595, -0.00974109267696527,
   -0.007968015032797376, -0.007801513845528344,
   -0.007535748903681969, -0.003543341967287925,
   0.0015083125553729722, 0.0023345972556147025,
   -0.0010043623069557037, -0.0025295765105203746,
   -0.0023701840891643634, -0.0005908186035024362,
   0.0029826252289082847, 0.004829048542117764,
   0.004488360022902081, 0.00002643748103005408,
   -0.0042100779212597295, -0.006170600558114495,
   -0.007267149164680168, -0.006825522903494639,
   -0.006899834372739123, -0.0073493916110062675,
   -0.009554351265163382, -0.011790297433830197,
   -0.010645796603734424, -0.0064661575394022106,
   -0.002026743466524137, -0.0004337034584909932,
   -0.0011172647031654614, -0.0017947816283674731,
   -0.00255615052036616, -0.0017721562881944813,
   -0.0002379619297227554, 0.0007130120121089036
};

#endif /* MPLAYER_AF_HRTF_H */
