TBLE2 ncep_reanal_params[] = {
{1, "Pressure", "Pa", "PRES"},
{2, "Pressure reduced to MSL", "Pa", "PRMSL"},
{3, "Pressure tendency", "Pa/s", "PTEND"},
{6, "Geopotential", "m^2/s^2", "GP"},
{7, "Geopotential height", "gpm", "HGT"},
{8, "Geometric height", "m", "DIST"},
{9, "Std dev of height", "m", "HSTDV"},
{10, "Variance of height", "m^2", "HVAR"},
{11, "Temp.", "K", "TMP"},
{12, "Virtual temp.", "K", "VTMP"},
{13, "Potential temp.", "K", "POT"},
{14, "Pseudo-adiabatic pot. temp.", "K", "EPOT"},
{15, "Max. temp.", "K", "T_MAX"},
{16, "Min. temp.", "K", "T_MIN"},
{17, "Dew point temp.", "K", "DPT"},
{18, "Dew point depression", "K", "DEPR"},
{19, "Lapse rate", "K/m", "LAPR"},
{20, "Visibility", "m", "VIS"},
{21, "Radar spectra (1)", "non-dim", "RDSP1"},
{22, "Radar spectra (2)", "non-dim", "RDSP2"},
{23, "Radar spectra (3)", "non-dim", "RDSP3"},
{25, "Temp. anomaly", "K", "TMP_A"},
{26, "Pressure anomaly", "Pa", "PRESA"},
{27, "Geopotential height anomaly", "gpm", "GPA"},
{28, "Wave spectra (1)", "non-dim", "WVSP1"},
{29, "Wave spectra (2)", "non-dim", "WVSP2"},
{30, "Wave spectra (3)", "non-dim", "WVSP3"},
{31, "Wind direction", "deg", "WDIR"},
{32, "Wind speed", "m/s", "WIND"},
{33, "u wind", "m/s", "U_GRD"},
{34, "v wind", "m/s", "V_GRD"},
{35, "Stream function", "m^2/s", "STRM"},
{36, "Velocity potential", "m^2/s", "V_POT"},
{37, "Montgomery stream function", "m^2/s^2", "MNTSF"},
{38, "Sigma coord. vertical velocity", "/s", "SGCVV"},
{39, "Pressure vertical velocity", "Pa/s", "V_VEL"},
{40, "Geometric vertical velocity", "m/s", "DZDT"},
{41, "Absolute vorticity", "/s", "ABS_V"},
{42, "Absolute divergence", "/s", "ABS_D"},
{43, "Relative vorticity", "/s", "REL_V"},
{44, "Relative divergence", "/s", "REL_D"},
{45, "Vertical u shear", "/s", "VUCSH"},
{46, "Vertical v shear", "/s", "VVCSH"},
{47, "Direction of current", "deg", "DIR_C"},
{48, "Speed of current", "m/s", "SP_C"},
{49, "u of current", "m/s", "UOGRD"},
{50, "v of current", "m/s", "VOGRD"},
{51, "Specific humidity", "kg/kg", "SPFH"},
{52, "Relative humidity", "%", "RH"},
{53, "Humidity mixing ratio", "kg/kg", "MIXR"},
{54, "Precipitable water", "kg/m^2", "P_WAT"},
{55, "Vapor pressure", "Pa", "VAPP"},
{56, "Saturation deficit", "Pa", "SAT_D"},
{57, "Evaporation", "kg/m^2", "EVP"},
{58, "Cloud Ice", "kg/m^2", "C_ICE"},
{59, "Precipitation rate", "kg/m^2/s", "PRATE"},
{60, "Thunderstorm probability", "%", "TSTM"},
{61, "Total precipitation", "kg/m^2", "A_PCP"},
{62, "Large scale precipitation", "kg/m^2", "NCPCP"},
{63, "Convective precipitation", "kg/m^2", "ACPCP"},
{64, "Snowfall rate water equiv.", "kg/m^2/s", "SRWEQ"},
{65, "Accum. snow", "kg/m^2", "WEASD"},
{66, "Snow depth", "m", "SNO_D"},
{67, "Mixed layer depth", "m", "MIXHT"},
{68, "Transient thermocline depth", "m", "TTHDP"},
{69, "Main thermocline depth", "m", "MTHD"},
{70, "Main thermocline anomaly", "m", "MTH_A"},
{71, "Total cloud cover", "%", "T_CDC"},
{72, "Convective cloud cover", "%", "CDCON"},
{73, "Low level cloud cover", "%", "L_CDC"},
{74, "Mid level cloud cover", "%", "M_CDC"},
{75, "High level cloud cover", "%", "H_CDC"},
{76, "Cloud water", "kg/m^2", "C_WAT"},
{78, "Convective snow", "kg/m^2", "SNO_C"},
{79, "Large scale snow", "kg/m^2", "SNO_L"},
{80, "Water temp.", "K", "WTMP"},
{81, "Land-sea mask", "1=land; 0=sea", "LAND"},
{82, "Deviation of sea level from mean", "m", "DSL_M"},
{83, "Surface roughness", "m", "SFC_R"},
{84, "Albedo", "%", "ALBDO"},
{85, "Soil temp.", "K", "TSOIL"},
{86, "Soil moisture content", "kg/m^2", "SOIL_M"},
{87, "Vegetation", "%", "VEG"},
{88, "Salinity", "kg/kg", "SALTY"},
{89, "Density", "kg/m^3", "DEN"},
{90, "Runoff", "kg/m^2", "RUNOF"},
{91, "Ice concentration", "ice=1;no ice=0", "ICE_C"},
{92, "Ice thickness", "m", "ICETK"},
{93, "Direction of ice drift", "deg", "DICED"},
{94, "Speed of ice drift", "m/s", "SICED"},
{95, "u of ice drift", "m/s", "U_ICE"},
{96, "v of ice drift", "m/s", "V_ICE"},
{97, "Ice growth rate", "m/s", "ICE_G"},
{98, "Ice divergence", "/s", "ICE_D"},
{99, "Snow melt", "kg/m^2", "SNO_M"},
{100, "Sig height of wind waves and swell", "m", "HTSGW"},
{101, "Direction of wind waves", "deg", "WVDIR"},
{102, "Sig height of wind waves", "m", "WVHGT"},
{103, "Mean period of wind waves", "s", "WVPER"},
{104, "Direction of swell waves", "deg", "SWDIR"},
{105, "Sig height of swell waves", "m", "SWELL"},
{106, "Mean period of swell waves", "s", "SWPER"},
{107, "Primary wave direction", "deg", "DIRPW"},
{108, "Primary wave mean period", "s", "PERPW"},
{109, "Secondary wave direction", "deg", "DIRSW"},
{110, "Secondary wave mean period", "s", "PERSW"},
{111, "Net short wave (surface)", "W/m^2", "NSWRS"},
{112, "Net long wave (surface)", "W/m^2", "NLWRS"},
{113, "Net short wave (top)", "W/m^2", "NSWRT"},
{114, "Net long wave (top)", "W/m^2", "NLWRT"},
{115, "Long wave", "W/m^2", "LWAVR"},
{116, "Short wave", "W/m^2", "SWAVR"},
{117, "Global radiation", "W/m^2", "G_RAD"},
{121, "Latent heat flux", "W/m^2", "LHTFL"},
{122, "Sensible heat flux", "W/m^2", "SHTFL"},
{123, "Boundary layer dissipation", "W/m^2", "BLYDP"},
{124, "Zonal momentum flux", "N/m^2", "U_FLX"},
{125, "Meridional momentum flux", "N/m^2", "V_FLX"},
{126, "Wind mixing energy", "J", "WMIXE"},
{127, "Image data", "integer", "IMG_D"},
{128, "Mean sea level pressure (Std Atm)", "Pa", "MSLSA"},
{129, "Mean sea level pressure (MAPS)", "Pa", "MSLMA"},
{130, "Mean sea level pressure (ETA model)", "Pa", "MSLET"},
{131, "Surface lifted index", "K", "LFT_X"},
{132, "Best (4-layer) lifted index", "K", "4LFTX"},
{133, "K index", "K", "K_X"},
{134, "Sweat index", "K", "S_X"},
{135, "Horizontal moisture divergence", "kg/kg/s", "MCONV"},
{136, "Vertical speed shear", "1/s", "VW_SH"},
{137, "3-hr pressure tendency", "Pa/s", "TSLSA"},
{138, "Brunt-Vaisala frequency^2", "1/s^2", "BVF_2"},
{139, "Potential vorticity (mass-weighted)", "1/s/m", "PV_MW"},
{140, "Categorical rain", "yes=1;no=0", "CRAIN"},
{141, "Categorical freezing rain", "yes=1;no=0", "CFRZR"},
{142, "Categorical ice pellets", "yes=1;no=0", "CICEPL"},
{143, "Categorical snow", "yes=1;no=0", "CSNOW"},
{144, "Volumetric soil moisture", "fraction", "SOILW"},
{145, "Potential evaporation rate", "W/m^2", "PEVPR"},
{146, "Cloud work function", "J/kg", "CWORK"},
{147, "Zonal gravity wave stress", "N/m^2", "U_GWD"},
{148, "Meridional gravity wave stress", "N/m^2", "V_GWD"},
{149, "Potential vorticity", "m^2/s/kg", "PV"},
{153, "Moisture flux divergence", "gr/gr*m/s/m", "MFXDV"},
{155, "Ground heat flux", "W/m^2", "GFLUX"},
{156, "Convective inhibition", "J/kg", "CIN"},
{157, "Convective Avail. Pot. Energy", "J/kg", "CAPE"},
{158, "Turbulent kinetic energy", "J/kg", "TKE"},
{159, "Lifted parcel condensation pressure", "Pa", "CONDP"},
{160, "Clear sky upward solar flux", "W/m^2", "CSUSF"},
{161, "Clear sky downward solar flux", "W/m^2", "CSDSF"},
{162, "Clear sky upward long wave flux", "W/m^2", "CSULF"},
{163, "Clear sky downward long wave flux", "W/m^2", "CSDLF"},
{164, "Cloud forcing net solar flux", "W/m^2", "CFNSF"},
{165, "Cloud forcing net long wave flux", "W/m^2", "CFNLF"},
{166, "Visible beam downward solar flux", "W/m^2", "VBDSF"},
{167, "Visible diffuse downward solar flux", "W/m^2", "VDDSF"},
{168, "Near IR beam downward solar flux", "W/m^2", "NBDSF"},
{169, "Near IR diffuse downward solar flux", "W/m^2", "NDDSF"},
{170, "U wind stress", "N/m^2", "USTR"},
{171, "V wind stress", "N/m^2", "VSTR"},
{172, "Momentum flux", "N/m^2", "M_FLX"},
{173, "Mass point model surface", "non-dim", "LMH"},
{174, "Velocity point model surface", "non-dim", "LMV"},
{175, "Model layer number (from bottom up)", "non-dim", "MLYNO"},
{176, "latitude(-90 to +90)", "deg", "NLAT"},
{177, "east longitude (0-360)", "deg", "ELON"},
{178, "Mass weighted u", "gm/m*K*s", "UMAS"},
{179, "Mass weighted v", "gm/m*K*s", "VMAS"},
{180, "corrected precip", "kg/m^2/s", "XPRATE"},
{181, "x-gradient of log pressure", "1/m", "LPS_X"},
{182, "y-gradient of log pressure", "1/m", "LPS_Y"},
{183, "x-gradient of height", "m/m", "HGT_X"},
{184, "y-gradient of height", "m/m", "HGT_Y"},
{185, "Std dev of Geop. hgt.", "m", "STDZ"},
{186, "Std dev of zonal wind", "m/s", "STDU"},
{187, "Std dev of meridional wind", "m/s", "STDV"},
{188, "Std dev of spec. hum.", "gm/gm", "STDQ"},
{189, "Std dev of temp.", "K", "STDT"},
{190, "Covariance u and omega", "m/s*Pa/s", "CBUW"},
{191, "Covariance v and omega", "m/s*Pa/s", "CBVW"},
{192, "Covariance u and specific hum", "m/s*gm/gm", "CBUQ"},
{193, "Covariance v and specific hum", "m/s*gm/gm", "CBVQ"},
{194, "Covariance T and omega", "K*Pa/s", "CBTW"},
{195, "Covariance spec. hum and omega", "gm/gm*Pa/s", "CBQW"},
{196, "Covariance v and u", "m^2/s^2", "CBMZW"},
{197, "Covariance u and T", "K*m/s", "CBTZW"},
{198, "Covariance v and T", "K*m/s", "CBTMW"},
{199, "Std dev of Rel. Hum.", "%", "STDRH"},
{200, "Std dev of time tend of geop. hgt", "m", "SDTZ"},
{201, "Ice-free water surface", "%", "ICWAT"},
{202, "Std dev of time tend of zonal wind", "m/s", "SDTU"},
{203, "Std dev of time tend of merid wind", "m/s", "SDTV"},
{204, "Downward solar radiation flux", "W/m^2", "DSWRF"},
{205, "Downward long wave flux", "W/m^2", "DLWRF"},
{206, "Std dev of time tend of spec. hum", "gm/gm", "SDTQ"},
{207, "Moisture availability", "%", "MSTAV"},
{208, "Exchange coefficient", "kg*m/m^3/s", "SFEXC"},
{209, "No. of mixed layers next to sfc", "integer", "MIXLY"},
{210, "Std dev of time tend of temp.", "K", "SDTT"},
{211, "Upward solar radiation flux", "W/m^2", "USWRF"},
{212, "Upward long wave flux", "W/m^2", "ULWRF"},
{213, "Non-convective cloud", "%", "CDLYR"},
{214, "Convective precip. rate", "kg/m^2/s", "CPRAT"},
{215, "Temp. tendency by all physics", "K/s", "TTDIA"},
{216, "Temp. tendency by all radiation", "K/s", "TTRAD"},
{217, "Temp. tendency by nonrad physics", "K/s", "TTPHY"},
{218, "Precipitation index", "fraction", "PREIX"},
{219, "Std dev of IR T over 1x1 deg area", "K", "TSD1D"},
{220, "Natural log of surface pressure", "ln(kPa)", "NLSGP"},
{221, "Std dev of time tend of rel hum", "%", "SDTRH"},
{222, "5-wave geopotential height", "gpm", "5WAVH"},
{223, "Plant canopy surface water", "kg/m^2", "C_WAT"},
{224, "Max. stomato plant resistance", "s/m", "PLTRS"},
{225, "RH-type cloud cover", "%", "RHCLD"},
{226, "Blackadar's mixing length scale", "m", "BMIXL"},
{227, "Asymptotic mixing length scale", "m", "AMIXL"},
{228, "Pot. evaporation", "kg/m^2", "PEVAP"},
{229, "Snow melt heat flux", "W/m^2", "SNOHF"},
{230, "Snow sublimation heat flux", "W/m^2", "SNOEV"},
{231, "Convective cloud mass flux", "Pa/s", "MFLUX"},
{232, "Downward total radiation flux", "W/m^2", "DTRF"},
{233, "Upward total radiation flux", "W/m^2", "UTRF"},
{234, "Baseflow-groundwater runoff", "kg/m^2", "BGRUN"},
{235, "Storm surface runoff", "kg/m^2", "SSRUN"},
{237, "Total column ozone", "Dobson", "OZONE"},
{238, "Snow cover", "%", "SNOWC"},
{239, "Snow temp.", "K", "SNOT"},
{240, "Permanent snow points", "mask", "GLCR"},
{241, "Large scale condensation heating", "K/s", "LRGHR"},
{242, "Deep convective heating", "K/s", "CNVHR"},
{243, "Deep convective moistening", "kg/kg/s", "CNVMR"},
{244, "Shallow convective heating", "K/s", "SHAHR"},
{245, "Shallow convective moistening", "kg/kg/s", "SHAMR"},
{246, "Vertical diffusion heating", "K/s", "VDFHR"},
{247, "Vertical diffusion zonal accel", "m/s^2", "VDFUA"},
{248, "Vertical diffusion meridional accel", "m/s^2", "VDFVA"},
{249, "Vertical diffusion moistening", "kg/kg/s", "VDFMR"},
{250, "Solar radiative heating", "K/s", "SWHR"},
{251, "Longwave radiative heating", "K/s", "LWHR"},
{252, "Drag coefficient", "non-dim", "CD"},
{253, "Friction velocity", "m/s", "FRICV"},
{254, "Richardson number", "non-dim", "RI"},
};
