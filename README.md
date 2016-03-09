Fido
====

Mail gateway between the Retroshare message network and the SMTP network.

Dependencies:
* Retroshare
* mimetic (http://www.codesink.org/index.html). On Debian, simply install libmimetic-dev
* A Maildir compliant SMTP server


1. Get the Retroshare sources from the Repository (0.6.*) and build it
2. clone the git repository into the plugin directory of the Retroshare sources
3. edit p3Fido.cpp and enter your GXID and mailserver
4. qmake && make
5. cp libFido.so.1.0.0 ~/.retroshare/extensions/Fido.so

then start Retroshare

Fido uses the GXS ID as an address to forward emails into the Retroshare network. So an email must have the format:
GXS-ID@gateway
e.g.
49dc68a38e19c55f07e971bacb12f6b6@ns3.ativel.com
