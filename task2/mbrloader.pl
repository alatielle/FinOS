#!/usr/bin/perl
my $file = $ARGV[0];
my $output = "output";
my $loader;
my $stream;
die "Argument needed!" if ( scalar(@ARGV) == 0 );
open my $F, '<', $file or die "Can't open the file $file: $!";
open my $O, '>', $output;
binmode $F;
binmode $O;
die "Failed to read from $file" if ( (read $F, $stream, 510) != 510 );
while( read $F, $_, 1 ) {
	$_ = unpack "H2", $_;
	if ( $_ =~ /55/ ) {
		die "Failed to read from $file" if ( (read $F, $_, 1) != 1 );
		$_ = unpack "H2", $_;
		if ( $_ =~ /aa/ ) {
			die "Failed to change position in $file" if ( (seek $F, -512, 1) != 1 );
			die "Failed to read from $file" if ( (read $F, $stream, 512) != 512 );
			print $O $stream;
			close $F;
			close $O;
			system ( "ndisasm $output > dis.txt" ) == 0	or die("ndisasm failure: $?");
			exit 0;
		}
	}
}
die "Failed to find master boot record in $file: $!";