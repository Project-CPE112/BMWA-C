staName: is station name like Broadway
staShortCode: is station code like BDY
staFullCode: is station line with station code like MTR_BDY
connectionWith: is other transit that not rail system like boat PS: null if not transit with anything
conCount: connected station count (in the same line) PS: Value can be (0,1,2,3)
con1sta: connected station #1 full code like MTR_BRD PS: NULL IF conCount is 0
con1time: time to travel from MTR_BDY to MTR_BRD PS: NULL IF conCount is 0
con1platform: platform of a train at MTR_BDY that heading to MTR_BRD PS: NULL IF conCount is 0
con2sta: connected station #2 full code like MTR_BRA PS: NULL IF conCount is 1
con2time: time to travel from MTR_BDY to MTR_BRA PS: NULL IF conCount is 1
con2platform: platform of a train at MTR_BDY that heading to MTR_BRA PS: NULL IF conCount is 1
con3sta: connected station #3 full code like MTR_BRJ PS: NULL IF conCount is 2
con3time: time to travel from MTR_BDY to MTR_BRJ PS: NULL IF conCount is 2
con3platform: platform of a train at MTR_BDY that heading to MTR_BRJ PS: NULL IF conCount is 2
intCount: connected station count (in the other line) PS: Value can be (0,1,2,3)
int1sta: connected station #1 full code like BTS_CEN PS: NULL IF intCount is 0
int1time: time to transit from MTR_BDY to BTS_CEN PS: NULL IF intCount is 0
int2sta: connected station #2 full code like CED_BEM PS: NULL IF intCount is 1
int2time: time to transit from MTR_BDY to CED_BEM PS: NULL IF intCount is 1
int3sta: connected station #3 full code like KVM_MDX PS: NULL IF intCount is 2
int3time: time to transit from MTR_BDY to KVM_MDX PS: NULL IF intCount is 2

it store in csv file with this format
staName,staShortCode,staFullCode,connectionWith,conCount,con1sta,con1time,con1platform,con2sta,con2time,con2platform,con3sta,con3time,con3platform,intCount,int1sta,int1time,int2sta,int2time,int3sta,int3time

please make a DFS for me using the route from that csv file with C Language
that input the stationShortCode for start station as the first node of a this route
and input the stationShortCode for end station as the last node of a this route

and using DFS to find the best way to transit from start station to end station

then it will show 20 option of routes.



====================================================================================================================================================
| 1. |  20 stations | 400 Baht | 2 minutes |
| 2. |  40000 Stations | 40000000 Baht | 2 minutes |

Enter prefer routes: 1

MRTBL_BL01 Tha Phra |   40
MRTBL_BL02
MRTBL_BL03
MRTBL_BL04
MRTPK_PK30
MRTPK_PK20 Fucvk