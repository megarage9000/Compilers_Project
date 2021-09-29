

multilineStart \/\*
multilineEnd \*\/

%x START_MULTI
%x START_END_MULTI
%x IN_STRING

%%
\"          {ECHO;BEGIN IN_STRING;}
<IN_STRING>.*\"         {ECHO;BEGIN INITIAL;}
"//".*		{ }
{multilineStart}      {BEGIN START_MULTI;}
<START_MULTI>[^\*]*\*     { ;BEGIN START_END_MULTI;}
<START_END_MULTI>[^\/]   { ;BEGIN START_MULTI;}
<START_END_MULTI>\/|{multilineEnd}      { ;BEGIN INITIAL;}
.|\n	ECHO;
