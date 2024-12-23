{
  description = "basic c flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { nixpkgs, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
	inherit system;
      };
      test = pkgs.stdenv.mkDerivation rec {
	pname = "dwm";
	version = "6.5";
	src = ./.;
	buildInputs = with pkgs.xorg; [
	  libX11
	  libXinerama
	  libXft
	];
	prePatch = ''
	  sed -i "s@/usr/local@$out@" config.mk
	'';
	makeFlags = [ "CC=${pkgs.stdenv.cc.targetPrefix}cc" ];
      };
    in {
      packages.${system}.default = test;
    };
}
