#!/usr/bin/perl -w
# Licensed under the terms of the GNU GPL License version 2
$P =~ s@.*/@@g;
my $max_line_length = 80;
  --max-line-length=n        set the maximum line length, if exceeded, warn
  --show-types               show the message "types" in the output
	if (!$ignore_perl_version) {
		exit(1);
	}
	print "$P: no input files\n";
	exit(1);
	if ($quiet == 0 && keys %$hashRef) {
		print "NOTE: $prefix message types:";
		print "\n\n";
			__init_refok|
			__rcu
			__bitwise__|
our $Inline	= qr{inline|__always_inline|noinline};
our $Constant	= qr{$Float|$Binary|$Hex|$Int};
our $Compare    = qr{<=|>=|==|!=|<|>};
our $typeTypedefs = qr{(?x:
	printk(?:_ratelimited|_once|)|
	puts|
	qr{(?:unsigned\s+)?char},
	qr{(?:unsigned\s+)?short},
	qr{(?:unsigned\s+)?int},
	qr{(?:unsigned\s+)?long},
	qr{(?:unsigned\s+)?long\s+int},
	qr{(?:unsigned\s+)?long\s+long},
	qr{(?:unsigned\s+)?long\s+long\s+int},
	qr{unsigned},
	memory
	my $mods = "(?x:  \n" . join("|\n  ", @modifierList) . "\n)";
	my $all = "(?x:  \n" . join("|\n  ", @typeList) . "\n)";
			(?:(?:\s|\*|\[\])+\s*const|(?:\s|\*|\[\])+|(?:\s*\[\s*\])+)?
	$Declare	= qr{(?:$Storage\s+)?$Type};
our $LvalOrFunc	= qr{($Lval)\s*($balanced_parens{0,1})\s*};
our $FuncArg = qr{$Typecast{0,1}($LvalOrFunc|$Constant)};
	$string =~ s@^\s*\(\s*@@g;
	$string =~ s@\s*\)\s*$@@g;
		my $git_last_include_commit = `git log --no-merges --pretty=format:"%h%n" -1 -- include`;
		$files = `git ls-files "include/*.h"`;
	if ($file) {
		$formatted_email =~ s/$address.*$//;
	return ($name, $address, $comment);
			for (; ($n % 8) != 0; $n++) {
		# Comments we are wacking completly including the begin
	return "" if ($line !~ m/(\"[X]+\")/g);
					push(@modifierList, $modifier);
			push(@typeList, $possible);
	return defined $use_type{$_[0]} if (scalar keys %use_type > 0);
	return !defined $ignore_type{$_[0]};
	if (!show_type($_[1]) ||
	    (defined $tst_only && $_[2] !~ /\Q$tst_only\E/)) {
	my $line;
		$line = "$prefix$_[0]:$_[1]: $_[2]\n";
	} else {
		$line = "$prefix$_[0]: $_[2]\n";
	$line = (split('\n', $line))[0] . "\n" if ($terse);
	push(our @report, $line);
	if (report("ERROR", $_[0], $_[1])) {
	if (report("WARNING", $_[0], $_[1])) {
	if ($check && report("CHECK", $_[0], $_[1])) {
	my $source_indent = 8;
	return $last_openparen + 1;

	my $in_header_lines = 1;

			if ($1 =~ m@Documentation/kernel-parameters.txt$@) {
		if ($rawline=~/^\@\@ -\d+(?:,\d+)? \+(\d+)(,(\d+))? \@\@/) {
		if ($line=~/^\@\@ -\d+(?:,\d+)? \+(\d+)(,(\d+))? \@\@/) {
#make up the handle for any error we report on this line
		$prefix = "$filename:$realline: " if ($emacs && $file);
		$prefix = "$filename:$linenr: " if ($emacs && !$file);

		if ($line =~ /^\s*signed-off-by:/i) {
					$fixed[$linenr - 1] =
					$fixed[$linenr - 1] =
					$fixed[$linenr - 1] =
			my ($email_name, $email_address, $comment) = parse_email($email);
				if ("$dequoted$comment" ne $email &&
				    "<$email_address>$comment" ne $email &&
				    "$suggested_email$comment" ne $email) {
# Check for absolute kernel paths.
		if ($tree) {
			while ($line =~ m{(?:^|\s)(/\S*)}g) {
				my $file = $1;

				if ($file =~ m{^(.*?)(?::\d+)+:?$} &&
				    check_absolute_file($1, $herecurr)) {
					#
				} else {
					check_absolute_file($file, $herecurr);
				}
			}
		}

		    $rawline !~ /^(commit\b|from\b|[\w-]+:).+$/i) {
				$fixed[$linenr - 1] =~ s/[\s\015]+$//;
				$fixed[$linenr - 1] =~ s/\s+$//;
			my $msg_type = \&ERROR;
			$msg_type = \&CHK if ($file);
			&{$msg_type}("FSF_MAILING_ADDRESS",
				     "Do not include the paragraph about writing to the Free Software Foundation's mailing address from the sample GPL notice. The FSF has changed addresses in the past, and may do so again. Linux already includes a copy of the GPL.\n" . $herevet)
		    $line =~ /.\s*config\s+/) {
				if ($lines[$ln - 1] =~ /.\s*(?:bool|tristate)\s*\"/) {
				} elsif ($lines[$ln - 1] =~ /.\s*(?:---)?help(?:---)?$/) {
				if ($f =~ /^\s*config\s/) {
			WARN("CONFIG_DESCRIPTION",
			     "please write a paragraph that describes the config symbol fully\n" . $herecurr) if ($is_start && $is_end && $length < 4);
# discourage the addition of CONFIG_EXPERIMENTAL in Kconfig.
		    $line =~ /.\s*depends on\s+.*\bEXPERIMENTAL\b/) {
			WARN("CONFIG_EXPERIMENTAL",
			     "Use of CONFIG_EXPERIMENTAL is deprecated. For alternatives, see https://lkml.org/lkml/2012/10/23/580\n");
		if (defined $root && $realfile =~ /\.dts/ &&
		    $rawline =~ /^\+\s*compatible\s*=/) {
				my $dt_path =  $root . "/Documentation/devicetree/bindings/";
				$compat2 =~ s/\,[a-z]*\-/\,<\.\*>\-/;
				`grep -Erq "$compat|$compat2" $dt_path`;
				my $vendor = $compat;
				my $vendor_path = $dt_path . "vendor-prefixes.txt";
				next if (! -f $vendor_path);
				$vendor =~ s/^([a-zA-Z0-9]+)\,.*/$1/;
				`grep -Eq "$vendor" $vendor_path`;
					     "DT compatible string vendor \"$vendor\" appears un-documented -- check $vendor_path\n" . $herecurr);
		next if ($realfile !~ /\.(h|c|s|S|pl|sh)$/);

#line length limit
		if ($line =~ /^\+/ && $prevrawline !~ /\/\*\*/ &&
		    $rawline !~ /^.\s*\*\s*\@$Ident\s/ &&
		    !($line =~ /^\+\s*$logFunctions\s*\(\s*(?:(KERN_\S+\s*|[^"]*))?"[X\t]*"\s*(?:|,|\)\s*;)\s*$/ ||
		    $line =~ /^\+\s*"[^"]*"\s*(?:\s*|,|\)\s*;)\s*$/) &&
		    $length > $max_line_length)
		{
			WARN("LONG_LINE",
			     "line over $max_line_length characters\n" . $herecurr);
# Check for user-visible strings broken across lines, which breaks the ability
# to grep for the string.  Make exceptions when the previous string ends in a
# newline (multiple lines in one string constant) or '\t', '\r', ';', or '{'
# (common in inline assembly) or is a octal \123 or hexadecimal \xaf value
		if ($line =~ /^\+\s*"/ &&
		    $prevline =~ /"\s*$/ &&
		    $prevrawline !~ /(?:\\(?:[ntr]|[0-7]{1,3}|x[0-9a-fA-F]{1,2})|;\s*|\{\s*)"\s*$/) {
			WARN("SPLIT_STRING",
			     "quoted string split across lines\n" . $hereprev);
		}
# check for spaces before a quoted newline
		if ($rawline =~ /^.*\".*\s\\n/) {
			if (WARN("QUOTED_WHITESPACE_BEFORE_NEWLINE",
				 "unnecessary whitespace before a quoted newline\n" . $herecurr) &&
			    $fix) {
				$fixed[$linenr - 1] =~ s/^(\+.*\".*)\s+\\n/$1\\n/;
# Blackfin: use hi/lo macros
		if ($realfile =~ m@arch/blackfin/.*\.S$@) {
			if ($line =~ /\.[lL][[:space:]]*=.*&[[:space:]]*0x[fF][fF][fF][fF]/) {
				my $herevet = "$here\n" . cat_vet($line) . "\n";
				ERROR("LO_MACRO",
				      "use the LO() macro, not (... & 0xFFFF)\n" . $herevet);
			}
			if ($line =~ /\.[hH][[:space:]]*=.*>>[[:space:]]*16/) {
				my $herevet = "$here\n" . cat_vet($line) . "\n";
				ERROR("HI_MACRO",
				      "use the HI() macro, not (... >> 16)\n" . $herevet);
			}
		next if ($realfile !~ /\.(h|c|pl)$/);
# more than 8 must use tabs.
				$fixed[$linenr - 1] =~ s/^\+([ \t]+)/"\+" . tabify($1)/e;
				while ($fixed[$linenr - 1] =~
					   s/(^\+.*) {8,8}\t/$1\t\t/) {}
				while ($fixed[$linenr - 1] =~
		if ($^V && $^V ge 5.10.0 &&
		    $prevline =~ /^\+(\t*)(if \(|$Ident\().*(\&\&|\|\||,)\s*$/) {
					"\t" x ($pos / 8) .
					" "  x ($pos % 8);
						$fixed[$linenr - 1] =~
		if ($line =~ /^\+.*\*[ \t]*\)[ \t]+(?!$Assignment|$Arithmetic)/) {
				"No space is necessary after a cast\n" . $hereprev) &&
				$fixed[$linenr - 1] =~
				    s/^(\+.*\*[ \t]*\))[ \t]+/$1/;
		    $rawline =~ /^\+[ \t]*\*/) {
		if ($realfile =~ m@^(drivers/net/|net/)@ &&
		    $prevrawline =~ /^\+[ \t]*\/\*/ &&		#starting /*
			WARN("NETWORKING_BLOCK_COMMENT_STYLE",
			     "networking block comments start with * on subsequent lines\n" . $hereprev);
		if ($realfile =~ m@^(drivers/net/|net/)@ &&
		    $rawline !~ m@^\+[ \t]*\*/[ \t]*$@ &&	#trailing */
			WARN("NETWORKING_BLOCK_COMMENT_STYLE",
			     "networking block comments put the trailing */ on a separate line\n" . $herecurr);
				$fixed[$linenr - 1] =~ s/^\+([ \t]+)/"\+" . tabify($1)/e;
# discourage the addition of CONFIG_EXPERIMENTAL in #if(def).
		if ($line =~ /^\+\s*\#\s*if.*\bCONFIG_EXPERIMENTAL\b/) {
			WARN("CONFIG_EXPERIMENTAL",
			     "Use of CONFIG_EXPERIMENTAL is deprecated. For alternatives, see https://lkml.org/lkml/2012/10/23/580\n");
# Blackfin: don't use __builtin_bfin_[cs]sync
		if ($line =~ /__builtin_bfin_csync/) {
			my $herevet = "$here\n" . cat_vet($line) . "\n";
			ERROR("CSYNC",
			      "use the CSYNC() macro in asm/blackfin.h\n" . $herevet);
		}
		if ($line =~ /__builtin_bfin_ssync/) {
			my $herevet = "$here\n" . cat_vet($line) . "\n";
			ERROR("SSYNC",
			      "use the SSYNC() macro in asm/blackfin.h\n" . $herevet);
		}

		if ($linenr >= $suppress_statement &&
		if ($line =~ /(.*)\b((?:if|while|for|switch)\s*\(|do\b|else\b)/ && $line !~ /^.\s*\#/) {
			if ($ctx !~ /{\s*/ && defined($lines[$ctx_ln -1]) && $lines[$ctx_ln - 1] =~ /^\+\s*{/) {
		if ($line =~ /\b(?:(?:if|while|for)\s*\(|do\b)/ && $line !~ /^.\s*#/ && $line !~ /\}\s*while\s*/) {

			# Find out how long the conditional actually is.
			my @newlines = ($c =~ /\n/gs);
			my $cond_lines = 1 + $#newlines;
			if ($check && (($sindent % 8) != 0 ||
			    ($sindent <= $indent && $s ne ''))) {
			ERROR("OPEN_BRACE",
			      "that open brace { should be on the previous line\n" . $hereprev);
				my $line = $fixed[$linenr - 1];
					$fixed[$linenr - 1] =~ s@\/\/(.*)$@/\* $comment \*/@;
		if ($line =~ /^\+(\s*$Type\s*$Ident\s*(?:\s+$Modifier))*\s*=\s*(0|NULL|false)\s*;/) {
				  "do not initialise globals to 0 or NULL\n" .
				      $herecurr) &&
				$fixed[$linenr - 1] =~ s/($Type\s*$Ident\s*(?:\s+$Modifier))*\s*=\s*(0|NULL|false)\s*;/$1;/;
		if ($line =~ /^\+.*\bstatic\s.*=\s*(0|NULL|false)\s*;/) {
				  "do not initialise statics to 0 or NULL\n" .
				$fixed[$linenr - 1] =~ s/(\bstatic\s.*?)\s*=\s*(0|NULL|false)\s*;/$1;/;
               }
		if ($line =~ /(\b$Type\s+$Ident)\s*\(\s*\)/) {
				$fixed[$linenr - 1] =~ s/(\b($Type)\s+($Ident))\s*\(\s*\)/$2 $3(void)/;
			}
		}

# check for uses of DEFINE_PCI_DEVICE_TABLE
		if ($line =~ /\bDEFINE_PCI_DEVICE_TABLE\s*\(\s*(\w+)\s*\)\s*=/) {
			if (WARN("DEFINE_PCI_DEVICE_TABLE",
				 "Prefer struct pci_device_id over deprecated DEFINE_PCI_DEVICE_TABLE\n" . $herecurr) &&
			    $fix) {
				$fixed[$linenr - 1] =~ s/\b(?:static\s+|)DEFINE_PCI_DEVICE_TABLE\s*\(\s*(\w+)\s*\)\s*=\s*/static const struct pci_device_id $1\[\] = /;
		    $line !~ /\b__bitwise(?:__|)\b/) {
					$fixed[$linenr - 1] =~
					$fixed[$linenr - 1] =~
# # no BUG() or BUG_ON()
# 		if ($line =~ /\b(BUG|BUG_ON)\b/) {
# 			print "Try to use WARN_ON & Recovery code rather than BUG() or BUG_ON()\n";
# 			print "$herecurr";
# 			$clean = 0;
# 		}
"Prefer printk_ratelimited or pr_<level>_ratelimited to printk_ratelimit\n" . $herecurr);
# printk should use KERN_* levels.  Note that follow on printk's on the
# same line do not need a level, so we use the current block context
# to try and find and validate the current printk.  In summary the current
# printk includes all preceding printk's which have no newline on the end.
# we assume the first bad printk is the one to report.
		if ($line =~ /\bprintk\((?!KERN_)\s*"/) {
			my $ok = 0;
			for (my $ln = $linenr - 1; $ln >= $first_line; $ln--) {
				#print "CHECK<$lines[$ln - 1]\n";
				# we have a preceding printk if it ends
				# with "\n" ignore it, else it is to blame
				if ($lines[$ln - 1] =~ m{\bprintk\(}) {
					if ($rawlines[$ln - 1] !~ m{\\n"}) {
						$ok = 1;
					}
					last;
				}
			}
			if ($ok == 0) {
				WARN("PRINTK_WITHOUT_KERN_LEVEL",
				     "printk() should include KERN_ facility level\n" . $herecurr);
			}
			     "Prefer netdev_$level2(netdev, ... then dev_$level2(dev, ... then pr_$level(...  to printk(KERN_$orig ...\n" . $herecurr);
		}

		if ($line =~ /\bpr_warning\s*\(/) {
			if (WARN("PREFER_PR_LEVEL",
				 "Prefer pr_warn(... to pr_warning(...\n" . $herecurr) &&
			    $fix) {
				$fixed[$linenr - 1] =~
				    s/\bpr_warning\b/pr_warn/;
			}
		if (($line=~/$Type\s*$Ident\(.*\).*\s\{/) and
		    !($line=~/\#\s*define.*do\s\{/) and !($line=~/}/)) {
			ERROR("OPEN_BRACE",
			      "open brace '{' following function declarations go on the next line\n" . $herecurr);
			ERROR("OPEN_BRACE",
			      "open brace '{' following $1 go on the same line\n" . $hereprev);
				$fixed[$linenr - 1] =~
#
# the $Declare variable will capture all spaces after the type
# so check it for trailing missing spaces or multiple spaces
		if ($line =~ /^.\s*($Declare)\((\s*)\*(\s*)$Ident(\s*)\)(\s*)\(/) {
			if ($declare !~ /\s$/) {
			elsif ($declare =~ /\s{2,}$/) {
				WARN("SPACING",
				     "Multiple spaces after return type\n" . $herecurr);
			}
				$fixed[$linenr - 1] =~
				    s/^(.\s*$Declare)\(\s*\*\s*($Ident)\s*\)\s*\(/rtrim($1) . " " . "\(\*$2\)\("/ex;
			    $prefix !~ /[{,]\s+$/) {
				    $fixed[$linenr - 1] =~
					$fixed[$linenr - 1] =~
				    $ca =~ /\s$/ && $cc =~ /^\s*,/) {
				#   :   when part of a bitfield
				} elsif ($op eq '->' || $opv eq ':B') {
				# , must have a space on the right.
							$good = $fix_elements[$n] . trim($fix_elements[$n + 1]) . " ";
					if ($ctx =~ /Wx[^WCE]|[^WCE]xW/) {
					    	$ok = 1;
						my $msg_type = \&ERROR;
						$msg_type = \&CHK if (($op eq '?:' || $op eq '?' || $op eq ':') && $ctx =~ /VxV/);
						if (&{$msg_type}("SPACING",
								 "spaces required around that '$op' $at\n" . $hereptr)) {
			if ($fix && $line_fixed && $fixed_line ne $fixed[$linenr - 1]) {
				$fixed[$linenr - 1] = $fixed_line;
				1 while $fixed[$linenr - 1] =~
		if (($line =~ /\(.*\)\{/ && $line !~ /\($Type\){/) ||
		    $line =~ /do\{/) {
				$fixed[$linenr - 1] =~ s/^(\+.*(?:do|\))){/$1 {/;
		if ($line =~ /}(?!(?:,|;|\)))\S/) {
				$fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~
# Return is not a function.
			if ($^V && $^V ge 5.10.0 &&
			    $stat =~ /^.\s*return\s*$balanced_parens\s*;\s*$/) {
				ERROR("RETURN_PARENTHESES",
				      "return is not a function, parentheses are not required\n" . $herecurr);

		if ($^V && $^V ge 5.10.0 &&
# Return of what appears to be an errno should normally be -'ve
		if ($line =~ /^.\s*return\s*(E[A-Z]*)\s*;/) {
				     "return of an errno should typically be -ve (return -$1)\n" . $herecurr);
				$fixed[$linenr - 1] =~
			$s =~ s/$;//g; 	# Remove any comments
			$s =~ s/$;//g; 	# Remove any comments
			      "trailing statements should be on next line\n" .
		if ($prevline=~/}\s*$/ and $line=~/^.\s*else\s*/ and
						$previndent == $indent) {
			ERROR("ELSE_AFTER_BRACE",
			      "else should follow close brace '}'\n" . $hereprev);
		if ($prevline=~/}\s*$/ and $line=~/^.\s*while\s*/ and
						$previndent == $indent) {
				ERROR("WHILE_AFTER_BRACE",
				      "while should follow close brace '}'\n" . $hereprev);
#gcc binary extension
			if ($var =~ /^$Binary$/) {
				if (WARN("GCC_BINARY_CONSTANT",
					 "Avoid gcc v4.3+ binary constant extension: <$var>\n" . $herecurr) &&
				    $fix) {
					my $hexval = sprintf("0x%x", oct($var));
					$fixed[$linenr - 1] =~
					    s/\b$var\b/$hexval/;
				}
			}

#Ignore SI style variants like nS, mV and dB (ie: max_uV, regulator_min_uA_show)
			    $var !~ /^(?:[a-z_]*?)_?[a-z][A-Z](?:_[a-z_]+)?$/) {
				$fixed[$linenr - 1] =~ s/\s+$//;
#warn if <asm/foo.h> is #included and <linux/foo.h> is available (uses RAW line)
				if ($realfile =~ m{^arch/}) {
					CHK("ARCH_INCLUDE_LINUX",
					    "Consider using #include <linux/$file> instead of <asm/$file>\n" . $herecurr);
				} else {
					WARN("INCLUDE_LINUX",
					     "Use #include <linux/$file> instead of <asm/$file>\n" . $herecurr);
			$dstat =~ s/^.\s*\#\s*define\s+$Ident(?:\([^\)]*\))?\s*//;
			       $dstat =~ s/\[[^\[\]]*\]/1/)
			# Flatten any obvious string concatentation.
			while ($dstat =~ s/("X*")\s*$Ident/$1/ ||
			       $dstat =~ s/$Ident\s*("X*")/$1/)
				^\"|\"$
			    $dstat !~ /^'X'$/ &&					# character constants
				$ctx =~ s/\n*$//;
				my $herectx = $here . "\n";
				my $cnt = statement_rawlines($ctx);

				for (my $n = 0; $n < $cnt; $n++) {
					$herectx .= raw_line($linenr, $n) . "\n";
				}

				if ($dstat =~ /;/) {
					      "Macros with complex values should be enclosed in parenthesis\n" . "$herectx");
		if ($^V && $^V ge 5.10.0 &&
				my $herectx = $here . "\n";

				for (my $n = 0; $n < $cnt; $n++) {
					$herectx .= raw_line($linenr, $n) . "\n";
				}
# make sure symbols are always wrapped with VMLINUX_SYMBOL() ...
# all assignments may have only one of the following with an assignment:
#	.
#	ALIGN(...)
#	VMLINUX_SYMBOL(...)
		if ($realfile eq 'vmlinux.lds.h' && $line =~ /(?:(?:^|\s)$Ident\s*=|=\s*$Ident(?:\s|$))/) {
			WARN("MISSING_VMLINUX_SYMBOL",
			     "vmlinux.lds.h needs VMLINUX_SYMBOL() around C-visible symbols\n" . $herecurr);
		}

				my $herectx = $here . "\n";

				for (my $n = 0; $n < $cnt; $n++) {
					$herectx .= raw_line($linenr, $n) . "\n";
				}
			CHK("BRACES",
			    "Blank lines aren't necessary before a close brace '}'\n" . $hereprev);
			CHK("BRACES",
			    "Blank lines aren't necessary after an open brace '{'\n" . $hereprev);
			     "Use of volatile is usually wrong: see Documentation/volatile-considered-harmful.txt\n" . $herecurr);
			CHK("REDUNDANT_CODE",
			    "if this code is redundant consider removing it\n" .
				$herecurr);
			my $expr = '\s*\(\s*' . quotemeta($1) . '\s*\)\s*;';
			if ($line =~ /\b(kfree|usb_free_urb|debugfs_remove(?:_recursive)?)$expr/) {
				WARN('NEEDLESS_IF',
				     "$1(NULL) is safe this check is probably not required\n" . $hereprev);
					$fixed[$linenr - 1] =~ s/(\bstatic\s+(?:const\s+)?)(?:$attr\s+)?($NonptrTypeWithAttr)\s+(?:$attr\s+)?($Ident(?:\[[^]]*\])?)\s*([=;])\s*/"$1" . trim(string_find_replace($2, "\\s*$attr\\s*", " ")) . " " . trim(string_find_replace($3, "\\s*$attr\\s*", "")) . " $attr" . ("$4" eq ";" ? ";" : " = ")/e;
				$fixed[$linenr - 1] =~
				my $lead = $fixed[$linenr - 1] =~
				$fixed[$linenr - 1] =~ s/(^\+\s*(?:static\s+))/$lead/;
			if (! ($1 < 10) ) {
				    "usleep_range is preferred over udelay; see Documentation/timers/timers-howto.txt\n" . $line);
				     "msleep < 20ms can sleep for up to 20ms; see Documentation/timers/timers-howto.txt\n" . $line);
				$fixed[$linenr - 1] =~
		if ($line =~ /\b(mb|rmb|wmb|read_barrier_depends|smp_mb|smp_rmb|smp_wmb|smp_read_barrier_depends)\(/) {
		if ($line =~ /\b$Storage\b/ && $line !~ /^.\s*$Storage\b/) {
			     "storage class should be at the beginning of the declaration\n" . $herecurr)
				$fixed[$linenr - 1] =~ s/\b(__inline__|__inline)\b/inline/;
# Check for new packed members, warn to use care
		if ($line =~ /\b(__attribute__\s*\(\s*\(.*\bpacked|__packed)\b/) {
			WARN("NEW_PACKED",
			     "Adding new packed members is to be done with care\n" . $herecurr);
		}
				$fixed[$linenr - 1] =~ s/\b__attribute__\s*\(\s*\(\s*format\s*\(\s*printf\s*,\s*(.*)\)\s*\)\s*\)/"__printf(" . trim($1) . ")"/ex;
				$fixed[$linenr - 1] =~ s/\b__attribute__\s*\(\s*\(\s*format\s*\(\s*scanf\s*,\s*(.*)\)\s*\)\s*\)/"__scanf(" . trim($1) . ")"/ex;
				$fixed[$linenr - 1] =~ s/\bsizeof\s+((?:\*\s*|)$Lval|$Type(?:\s+$Lval|))/"sizeof(" . trim($1) . ")"/ex;
# check for line continuations in quoted strings with odd counts of "
		if ($rawline =~ /\\$/ && $rawline =~ tr/"/"/ % 2) {
			WARN("LINE_CONTINUATIONS",
			     "Avoid line continuations in quoted strings\n" . $herecurr);
		}

			if ($fmt ne "" && $fmt !~ /[^\\]\%/) {
					$fixed[$linenr - 1] =~ s/\bseq_printf\b/seq_puts/;
		if ($^V && $^V ge 5.10.0 &&
		    $stat =~ /^\+(?:.*?)\bmemset\s*\(\s*$FuncArg\s*,\s*$FuncArg\s*\,\s*$FuncArg\s*\)/s) {
		if ($^V && $^V ge 5.10.0 &&
		    $line =~ /^\+(?:.*?)\bmemcpy\s*\(\s*$FuncArg\s*,\s*$FuncArg\s*\,\s*ETH_ALEN\s*\)/s) {
			if (WARN("PREFER_ETHER_ADDR_COPY",
				 "Prefer ether_addr_copy() over memcpy() if the Ethernet addresses are __aligned(2)\n" . $herecurr) &&
			    $fix) {
				$fixed[$linenr - 1] =~ s/\bmemcpy\s*\(\s*$FuncArg\s*,\s*$FuncArg\s*\,\s*ETH_ALEN\s*\)/ether_addr_copy($2, $7)/;
			}
		}
		if ($^V && $^V ge 5.10.0 &&
		if ($^V && $^V ge 5.10.0 &&
				     "usleep_range should not use min == max args; see Documentation/timers/timers-howto.txt\n" . "$here\n$stat\n");
				     "usleep_range args reversed, use min then max; see Documentation/timers/timers-howto.txt\n" . "$here\n$stat\n");
		if ($^V && $^V ge 5.10.0 &&
		    $stat =~ /\bsscanf\b/ &&
			my $stat_real = raw_line($linenr, 0);
		        for (my $count = $linenr + 1; $count <= $lc; $count++) {
				$stat_real = $stat_real . "\n" . raw_line($count, 0);
			}
				$fixed[$linenr - 1] =~ s/(.*)\bextern\b\s*(.*)/$1$2/;
				    "__setup appears un-documented -- check Documentation/kernel-parameters.txt\n" . $herecurr);
# check for pointless casting of kmalloc return
		if ($line =~ /\*\s*\)\s*[kv][czm]alloc(_node){0,1}\b/) {
		if ($^V && $^V ge 5.10.0 &&
		    $line =~ /\b($Lval)\s*\=\s*(?:$balanced_parens)?\s*([kv][mz]alloc(?:_node)?)\s*\(\s*(sizeof\s*\(\s*struct\s+$Lval\s*\))/) {
		if ($^V && $^V ge 5.10.0 &&
		    $line =~ /\b($Lval)\s*\=\s*(?:$balanced_parens)?\s*krealloc\s*\(\s*\1\s*,/) {
# check for GFP_NOWAIT use
		if ($line =~ /\b__GFP_NOFAIL\b/) {
			WARN("__GFP_NOFAIL",
			     "Use of __GFP_NOFAIL is deprecated, no new users should be added\n" . $herecurr);
		}

				$fixed[$linenr - 1] =~ s/(\s*;\s*){2,}$/;/g;
# check for case / default statements not preceeded by break/fallthrough/switch
			while ($prevline > 1 && $count < 3 && !$has_break) {
				$has_break = 1 if ($fline =~ /\bswitch\b|\b(?:break\s*;[\s$;]*$|return\b|goto\b|continue\b)/);
				     "Possible switch case/default not preceeded by break or fallthrough comment\n" . $herecurr);
		if ($^V && $^V ge 5.10.0 &&
			my $ctx = '';
			my $herectx = $here . "\n";
			for (my $n = 0; $n < $cnt; $n++) {
				$herectx .= raw_line($linenr, $n) . "\n";
			}
				$fixed[$linenr - 1] =~ s/\b__FUNCTION__\b/__func__/g;
# check for __initcall(), use device_initcall() explicitly please
			     "please use device_initcall() instead of __initcall()\n" . $herecurr);
		}

# check for various ops structs, ensure they are const.
		my $struct_ops = qr{acpi_dock_ops|
				address_space_operations|
				backlight_ops|
				block_device_operations|
				dentry_operations|
				dev_pm_ops|
				dma_map_ops|
				extent_io_ops|
				file_lock_operations|
				file_operations|
				hv_ops|
				ide_dma_ops|
				intel_dvo_dev_ops|
				item_operations|
				iwl_ops|
				kgdb_arch|
				kgdb_io|
				kset_uevent_ops|
				lock_manager_operations|
				microcode_ops|
				mtrr_ops|
				neigh_ops|
				nlmsvc_binding|
				pci_raw_ops|
				pipe_buf_operations|
				platform_hibernation_ops|
				platform_suspend_ops|
				proto_ops|
				rpc_pipe_ops|
				seq_operations|
				snd_ac97_build_ops|
				soc_pcmcia_socket_ops|
				stacktrace_ops|
				sysfs_ops|
				tty_operations|
				usb_mon_operations|
				wd_ops}x;
		    $line =~ /\bstruct\s+($struct_ops)\b/) {
			     "struct $1 should normally be const\n" .
				$herecurr);
# check for %L{u,d,i} in strings
		my $string;
		while ($line =~ /(?:^|")([X\t]*)(?:"|$)/g) {
			$string = substr($rawline, $-[1], $+[1] - $-[1]);
			$string =~ s/%%/__/g;
			if ($string =~ /(?<!%)%L[udi]/) {
				WARN("PRINTF_L",
				     "\%Ld/%Lu are not-standard C, use %lld/%llu\n" . $herecurr);
				last;
			}
		if ($line =~ /debugfs_create_file.*S_IWUGO/ ||
		    $line =~ /DEVICE_ATTR.*S_IWUGO/ ) {
	if (!$is_patch) {
	if ($is_patch && $chk_signoff && $signoff == 0) {
		ERROR("MISSING_SIGN_OFF",
		      "Missing Signed-off-by: line(s)\n");
		print "\n" if ($quiet == 0);
		if ($^V lt 5.10.0) {
			print("NOTE: perl $^V is not modern enough to detect all possible issues.\n");
			print("An upgrade to at least perl v5.10.0 is suggested.\n\n");

			print "NOTE: whitespace errors detected, you may wish to use scripts/cleanpatch or\n";
			print "      scripts/cleanfile\n\n";
	hash_show_words(\%use_type, "Used");
	hash_show_words(\%ignore_type, "Ignored");

	if ($clean == 0 && $fix && "@rawlines" ne "@fixed") {
					print $f $fixed_line. "\n";

	if ($clean == 1 && $quiet == 0) {
		print "$vname has no obvious style problems and is ready for submission.\n"
	if ($clean == 0 && $quiet == 0) {
		print << "EOM";
$vname has style problems, please review.

If any of these errors are false positives, please report
them to the maintainer, see CHECKPATCH in MAINTAINERS.
EOM
	}
