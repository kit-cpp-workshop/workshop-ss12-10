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
void input( basic_istream < C, CT >& in ) {
	CT::int_type const LF = CT::to_int_type( cFacet.widen('\n') );	// get LF character
	in >> skipws;												// (is by default)
	vector < int > v;
	while(in) {													// read until an extraction failed
		int i;
		while( in >> i ) {										// read an int
			v.push_back(i);										// use that int read successfully
			in >> ws_noLF;										// skip all white spaces but '\n'
			if( CT::eq_int_type(LF, in.peek()) ) { break; }		// break loop on line end
		}
		/* use the vector v, watch out v.size() could be 0 */
	}
}
/*$ iomanip_begin $*/
template < class C, class CT >
basic_istream < C, CT >& ws_noLF( basic_istream < C, CT >& s )
/*$ iomanip_impl $*/{
	locale const& loc = s.getloc();
	ctype < C > const& cFacet = use_facet < ctype < C > > (loc);
	for( CT::int_type c = s.peek();							// read but not consume next character
	        s												// anything went wrong?
		 && cFacet.is(cFacet.space, CT::to_char_type(c))	// c must be a white space
		 && !CT::eq_int_type(LF, c);						// c must not be '\n'
	     c = s.peek() )										// read but not consume next character
	{ s.get(); }											// consume/discard next character
	
	return s;
}
/*$ read_line_end $*/

/*$ locale_magin_begin $*/
/*$locale_magic$*/template < typename C >
/*$locale_magic$*/class ctype_noLF : public ctype<C> {
/*$locale_magic$*/public:
/*$locale_magic$*/	ctype_noLF(ctype const& p) : ctype(m_table) {
/*$locale_magic$*/		copy(p.table(), p.table()+ctype<C>::table_size, m_table);
/*$locale_magic$*/		m_table[(unsigned char)'\n'] = ctype_base::cntrl;
/*$locale_magic$*/	}
/*$locale_magic$*/protected:
/*$locale_magic$*/	ctype_base::mask m_table[ctype<C>::table_size];
/*$locale_magic$*/};

template < class C, class CT >
void input( basic_istream < C, CT >& in ) {
	/*$locale_magic$*/locale oldLoc = in.getloc();
	/*$locale_magic$*/ctype_noLF<C>* pMyFac = new ctype_noLF<C>( use_facet< ctype<C> >(oldLoc) );
	/*$locale_magic$*/in.imbue( locale{oldLoc, pMyFac} );

	typename CT::int_type const LF = CT::to_int_type( pMyFac->widen('\n') );	// get LF character
	in >> skipws;												// (is by default)
	vector < int > v;
	while(in) {													// read until an extraction failed
		int i;
		while( in >> i ) {										// read an int
			v.push_back(i);										// use that int read successfully
			if( CT::eq_int_type(LF, in.peek()) )				// if line ends now ('\n' follows)
			{ in.get(); break; }								// discard '\n' and break loop
		}
		/* use the vector v, watch out v.size() could be 0 */
	}
	in.imbue(oldLoc);
}
/*$ locale_magin_end $*/
