#!/usr/bin/perl
my $file = $ARGV[0];
my $output = "output";
my $loader;
my $stream;
my $found = 0;
if ( !scalar(@ARGV) ) {
	die "Argument needed!";
}
open my $F, '<', $file or die "Can't open the file $file: $!";
binmode $F;
if ( (read $F, $stream, 510) != 510 ) {
	die "Failed to read from $file";
}
while( (read $F, $_, 1) == 1 ) {
	$_ = unpack "H2", $_;
	if ( $_ eq "55" ) {
		if ( (read $F, $_, 1) != 1 ) {
			die "Failed to read from $file";
		}
		$_ = unpack "H2", $_;
		if ( $_ eq "aa" ) {
			$found++;
			open my $O, '>', $output;
			binmode $O;
			if ( (seek $F, -512, 1) != 1 ) {
				die "Failed to change position in $file";
			}
			if ( (read $F, $stream, 512) != 512 ) {
				die "Failed to read from $file";
			}
			print $O $stream;
			close $O;
			system ( 'ndisasm '.$output.' > dis'.$found.'.txt' ) == 0 or die("ndisasm failure: $?");
		}
	}
}
close $F;
die "Failed to find master boot record in $file: $!" if !$found;