static const char *colors[][3]				= {							//color conf ColFg, ColBg, ColBorder
	[SchemeNorm]		= { "#bd93f9",	NULL,	"#444444" },
	[SchemeSel]			= { "#6666ff",	NULL, 	"#bd93f9" },
	[SchemeSelGlobal]	= { "#6666ff",	NULL, 	"#bd93f9" },
	[SchemeHid]			= { "#bd93f9",	NULL,	NULL },
	[SchemeSystray]		= { NULL,		"#434343",	NULL },				//alpha systemtray currently not supported
	[SchemeUnderline]	= { "#6666ff",	NULL,	NULL },
	[SchemeNormTag]		= { "#bd93f9", 	NULL,	NULL },
	[SchemeSelTag]		= { "#6666ff", 	NULL, 	NULL },
};
static const unsigned int alphas[][3]		= {							//opacity conf ColFg, ColBg, ColBorder
	[SchemeNorm]		= { OPAQUE,		baralpha,	borderalpha },
	[SchemeSel]			= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeSelGlobal]	= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeNormTag]		= { OPAQUE, 	baralpha, 	borderalpha },
	[SchemeSelTag]		= { OPAQUE, 	baralpha, 	borderalpha },
//	[SchemeSystray]		= { OPAQUE, 	baralpha, 	borderalpha },
};