# teiq

This is a little tool for "grepping" TEI files with XPaths.  There is nothing you can do with it that can't be done with xmllint, but it's a smaller binary, the code is a bit more "modern" (also: less portable), and it's entirely focused on TEI texts.  It's main purpose is to allow things like:

	$ teiq -x "//tei:titleStmt" *.xml
