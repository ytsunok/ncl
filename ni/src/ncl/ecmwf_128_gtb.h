TBLE2 ecmwf_128_params[] = {
{1, "Stream Function", "m**2 s**-1", "STRM"},
{2, "Velocity Potential", "m**2 s**-1", "VPOT"},
{3, "Potential Temperature", "K", "POT"},
{4, "Equivalent Potential Temperature", "K", "EPOT"},
{5, "Saturated Equivalent Potential Temperature", "K", "SEPOT"},
{11, "u-component of Divergent Wind", "m s**-1", "UDIV"},
{12, "v-component of Divergent Wind", "m s**-1", "VDIV"},
{13, "u-component of Rotational Wind", "m s**-1", "UROT"},
{14, "v-component of Rotational Wind", "m s**-1", "VROT"},
{21, "Unbalanced component of temperature", "K", "UCTP"},
{22, "Unbalanced component of lnsp", "-", "UCLN"},
{23, "Unbalanced component of divergence", "s**-1", "UCDV"},
{26, "Lake cover", "(0-1)", "CL"},
{27, "Low vegetation cover", "(0-1)", "CVL"},
{28, "High vegetation cover", "(0-1)", "CVH"},
{29, "Type of low vegetation", "-", "TVL"},
{30, "Type of high vegetation", "-", "TVH"},
{31, "Sea ice cover", "(0-1)", "CI"},
{32, "Snow albedo", "(0-1)", "ASN"},
{33, "Snow density", "kg**-3", "RSN"},
{34, "Sea surface temperature (absolute)", "K", "SSTK"},
{35, "Ice surface temperature layer 1", "K", "ISTL1"},
{36, "Ice surface temperature layer 2", "K", "ISTL2"},
{37, "Ice surface temperature layer 3", "K", "ISTL3"},
{38, "Ice surface temperature layer 4", "K", "ISTL4"},
{39, "Volumetric soil water layer 1", "m**3 m**-3", "SWVL1"},
{40, "Volumetric soil water layer 2", "m**3 m**-3", "SWVL2"},
{41, "Volumetric soil water layer 3", "m**3 m**-3", "SWVL3"},
{42, "Volumetric soil water layer 4", "m**3 m**-3", "SWVL4"},
{43, "Soil Type", "-", "SLT"},
{44, "Snow evaporation", "m of water", "ES"},
{45, "Snowmelt", "m of water", "SMLT"},
{46, "Solar duration", "s", "SDUR"},
{47, "Direct solar radiation", "w m**-2", "DSRP"},
{48, "Magnitude of surface stress", "N m**-2 s", "MAGSS"},
{49, "Wind gust at 10 metres", "m s**-1", "10FG"},
{50, "Large-scale precipitation fraction", "s", "LSPF"},
{51, "Maximum 2 metre temperature", "K", "MX2T24"},
{52, "Minimum 2 metre temperature", "K", "MN2T24"},
{53, "Montgomery potential", "m**2 s**-2", "MONT"},
{54, "Pressure", "Pa", "PRES"},
{60, "Potential vorticity", "K m**2 kg**-1 s**-1", "PV"},
{127, "Atmospheric tide", "-", "AT"},
{128, "Budget values", "-", "BV"},
{129, "Geopotential (at the surface = orography)", "m**2 s**-2", "Z"},
{130, "Temperature", "K", "T"},
{131, "U-velocity", "m s**-1", "U"},
{132, "V-velocity", "m s**-1", "V"},
{133, "Specific humidity", "kg kg**-1", "Q"},
{134, "Surface pressure", "Pa", "SP"},
{135, "Vertical velocity", "Pa s**-1", "W"},
{136, "Total column water", "kg m**-2", "TWC"},
{137, "Precipitable water content", "kg m**-2", "PWC"},
{138, "Vorticity (relative)", "s**-1", "VO"},
{139, "Surf.temp/soil temp lev 1 (from 930804)", "K", "ST"},
{140, "Surf soil wet/soil wet lev1(from 930803)", "m (of water)", "SSW"},
{141, "Snow depth", "m (of water equivalent)", "SD"},
{142, "Large scale precipitation", "m", "LSP"},
{143, "Convective precipitation", "m", "CP"},
{144, "Snow fall", "m(of water equivalent)", "SF"},
{145, "Boundary layer dissipation", "W m**-2 s", "BLD"},
{146, "Surface sensible heat flux", "W m**-2 s", "SSHF"},
{147, "Surface latent heat flux", "W m**-2 s", "SLHF"},
{148, "Surface stress/Charnock (from 980519)", "-", "SS_CHNK"},
{149, "Surface net radiation", "-", "SNR"},
{150, "Top net radiation", "-", "AIW"},
{151, "Mean sea level pressure", "Pa", "MSL"},
{152, "Log surface pressure", "-", "LNSP"},
{153, "Short wave heating rate", "K", "SWHR"},
{154, "Long wave heating rate", "K", "LWH"},
{155, "Divergence", "s**-1", "D"},
{156, "Height (geopotential)", "m", "GH"},
{157, "Relative humidity", "%", "R"},
{158, "Tendency of surface pressure", "Pa s**-1", "TSP"},
{159, "Boundary layer height", "m", "BLH"},
{160, "Standard deviation of orography", "-", "SDOR"},
{161, "Anisotropy of subgrid scale orography", "-", "ISOR"},
{162, "Angle of subgrid scale orography", "-", "ANOR"},
{163, "Slope of subgrid scale orography", "-", "SLOR"},
{164, "Total cloud cover", "(0 - 1)", "TCC"},
{165, "10 metre u wind component", "m s**-1", "10U"},
{166, "10 metre v wind component", "m s**-1", "10V"},
{167, "2 metre temperature", "K", "2T"},
{168, "2 metre dewpoint temperature", "K", "2D"},
{169, "Surface solar radiation downwards", "W m**-2 s", "SSRD"},
{170, "Deep soil tmp/soil temp lev2(from 930804)", "K", "DST"},
{171, "Deep soil wet/soil wet lev2(from 930803)", "m (of water)", "DSW"},
{172, "Land/sea mask", "(0-1)", "LSM"},
{173, "Surface roughness", "m", "SR"},
{174, "Albedo", "-", "AL"},
{175, "Surface thermal radiation downwards", "W m**-2 s", "STRD"},
{176, "Surface solar radiation", "W m**-2 s", "SSR"},
{177, "Surface thermal radiation", "W m**-2 s", "STR"},
{178, "Top solar radiation", "W m**-2 s", "TSR"},
{179, "Top thermal radiation", "W m**-2 s", "TTR"},
{180, "East/West surface stress", "N m**-2 s", "EWSS"},
{181, "North/South surface stress", "N m**-2 s", "NSSS"},
{182, "Evaporation", "m (of water)", "E"},
{183, "Clim deep soil tmp/soil tmp lev3(930804)", "K", "CDST"},
{184, "Clim deep soil wet/soil wet lev3(930803)", "m (of water)", "CDSW"},
{185, "Convective cloud cover", "(0 - 1)", "CCC"},
{186, "Low cloud cover", "(0 - 1)", "LCC"},
{187, "Medium cloud cover", "(0 - 1)", "MCC"},
{188, "High cloud cover", "(0 - 1)", "HCC"},
{189, "Sunshine duration", "s", "SUND"},
{190, "EW component subgrid orographic variance", "m**2", "EWOV"},
{191, "NS component subgrid orographic variance", "m**2", "NSOV"},
{192, "NWSE component subgrid orographic variance", "m**2", "NWOV"},
{193, "NESW component subgrid orographic variance", "m**2", "NEOV"},
{194, "Brightness temperature", "K", "BTMP"},
{195, "Lat. component of gravity wave stress", "N m**-2 s", "LGWS"},
{196, "Meridional component gravity wave stress", "N m**-2 s", "MGWS"},
{197, "Gravity wave dissipation", "W m**-2 s", "GWD"},
{198, "Skin reservoir content", "m (of water)", "SRC"},
{199, "Percentage of vegetation", "%", "VEG"},
{200, "Variance of sub-grid scale orography", "m**2", "VSO"},
{201, "Max 2m temp since previous post-processing", "K", "MX2T"},
{202, "Min 2m temp since previous post-processing", "K", "MN2T"},
{203, "Ozone mass mixing ratio", "kg kg**-1", "O3"},
{204, "Precip. analysis weights", "-", "PAW"},
{205, "Runoff*", "m", "RO"},
{206, "Total column ozone Dobson", "kg m**-2", "TCO3"},
{207, "10m. Windspeed (irresp of dir.)", "m s**-1", "10SI"},
{208, "Top net solar radiation clear sky", "W m**-2", "TSRC"},
{209, "Top upward thermal radiation clear sky", "W m**-2", "TTRC"},
{210, "Surface net solar radiation clear sky", "W m**-2", "SSRC"},
{211, "Surface net thermal radiation clear sky", "W m**-2", "STRC"},
{212, "Solar insulation", "W m**-2", "SI"},
{214, "Diabatic heating by radiation*", "K", "DHR"},
{215, "Diabatic heating by vertical diffusion", "K", "DHVD"},
{216, "Diabatic heating by cumulus convection", "K", "DHCC"},
{217, "Diabatic heating large-scale condensation", "K", "DHLC"},
{218, "Vertical diffusion of zonal wind", "m s**-1", "VDZW"},
{219, "Vertical diffusion of meridional wind", "m s**-1", "VDMW"},
{220, "EW gravity wave drag", "m s**-1", "EWGD"},
{221, "NS gravity wave drag", "m s**-1", "NSGD"},
{222, "Convective tendency of zonal wind", "m s**-1", "CTZW"},
{223, "Convective tendency of meridional wind", "m s**-1", "CTMW"},
{224, "Vertical diffusion of humidity", "kg kg**-1", "VDH"},
{225, "Humidity tendency by cumulus convection", "kg kg**-1", "HTCC"},
{226, "Humidity tendency large-scale condensation", "kg kg**-1", "HTLC"},
{227, "Change from removing negative humidity", "kg/kg s-1", "CRNH"},
{228, "Total precipitation", "m", "TP"},
{229, "Instantaneous X surface stress", "N m**-2", "IEWS"},
{230, "Instantaneous Y surface stress", "N m**-2", "INSS"},
{231, "Instantaneous surface Heat Flux", "W m**-2", "ISHF"},
{232, "Instantaneous Moisture Flux (evaporation)", "kg m**-2 s", "IE"},
{233, "Apparent Surface Humidity", "kg kg**-1", "ASQ"},
{234, "Log of surface roughness length for heat", "-", "LSRH"},
{235, "Skin Temperature", "K", "SKT"},
{236, "Soil temperature level 4", "K", "STL4"},
{237, "Soil wetness level 4", "m", "SWL4"},
{238, "Temperature of snow layer", "K", "TSN"},
{239, "Convective snow-fall", "m (of water equivalent)", "CSF"},
{240, "Large scale snow-fall", "m (of water equivalent)", "LSF"},
{241, "Accumulated cloud fraction tendency", "(-1 to 1)", "ACF"},
{242, "Accumulated liquid water tendency", "(-1 to 1)", "ALW"},
{243, "Forecast albedo", "-", "FAL"},
{244, "Forecast surface roughness", "m", "FSR"},
{245, "Forecast log of surface roughness for heat", "-", "FLSR"},
{246, "Cloud liquid water content", "kg kg**-1", "CLWC"},
{247, "Cloud ice water content", "kg kg**-1", "CIWC"},
{248, "Cloud cover", "(0 - 1)", "CC"},
{249, "Accumulated ice water tendency", "(-1 to 1)", "AIW"},
{250, "Ice Age", "(0 first-year 1 multi-year)", "ICE"},
{251, "Adiabatic tendency of temperature", "K", "ATTE"},
{252, "Adiabatic tendency of humidity", "kg kg**-1", "ATHE"},
{253, "Adiabatic tendency of zonal wind", "m s**-1", "ATZE"},
{254, "Adiabatic tendency of meridional wind", "m s**-1", "ATMW"},
{255, "Indicates a missing value", "-", ""},
};
