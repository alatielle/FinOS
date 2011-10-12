#!/usr/bin/perl
#use strict;
#use warnings;
my $file = $ARGV[0];
my $output = "output";
my $loader;
my $stream;
open my $F, '<', $file or die "Can't open the file $file: $!";
open my $O, '>', $output;
binmode $F;
binmode $O;
die("Failed to read from $file") if (read( $F, $stream, 512 ) != 512);
$_=unpack "H4",substr($stream,510,2);
if ($_ =~ /55aa/)
{
	print $O $stream;
	exit 0;
}
my $flag=0;
while(<$F>){
$_=unpack "H2",$_;
if ($flag) {
    $flag=0;
    if ($_ =~ /aa/) {
        seek($F, -512, 1);
        read($F, $stream, 512);
        print $O $stream;
        exit 0;
    }
}
$flag=1 if ($_ =~ /55/);
}
close $F;
close $O;