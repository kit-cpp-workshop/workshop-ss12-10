/*$ begin $*/
int i; int j;
/*$ bad_idea1 $*/
// schlechte Idee:
while( !cin.eof() )
{
	cin >> i >> j;
	// use i and j
}
/*$ bad_idea2 $*/
// nicht viel besser
while(cin)
{
	cin >> i >> j;
	// use i and j
}
/*$ good_idea1 $*/
// gute Idee
while( cin >> i >> j )
{
	// use i and j
}
/*$ good_idea2 $*/
// gute, flexiblere Idee
while(true)
{
	cin >> i >> j;
	if(!cin) { break; }
	// use i and j
}
/*$ read_line $*/
template < class C, class CT >
basic_istream < C, CT >& ws_noLF( basic_istream < C, CT >& s )
{
	std::locale const& loc = s.getloc();
	for( C c = s.peek();
	        s									// any error, or EOF?
		 && std::isspace(c, loc)				// c must be a white space
		 && s.widen('\n') != c;					// c must not be '\n'
	     c = s.peek() )
	{ s.get(); /* discard */ }
	
	return s;
}
/*$ locale_end $*/
/*$ facet $*/
template < class C, class CT >
basic_istream < C, CT >& ws_noLF( basic_istream < C, CT >& s )
{
	std::ctype < C > const& fac = std::use_facet < std::ctype < C > > (loc);
	for( C c = s.peek();
	        s									// any error, or EOF?
		 && fac.is(std::ctype_base::space, c)	// c must be a white space
		 && c != fac.widen('\n');				// c must not be '\n'
	     c = s.peek() )
	{ s.get(); /* discard */ }
	
	return s;
}
/*$ facet_end $*/
using Vec = vector < int >;
Vec v;
while(cin) {								// read until EOF or failure
	int i;
	while( cin >> i ) {						// read an int
		v.push_back(i);						// use that int read successfully

		cin >> ws_noLF;						// skip all white spaces but '\n'
		if( cin.widen('\n') == cin.peek() )	// if line ends now
		{ break; }
	}
	//- next line
	break;
}
