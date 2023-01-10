{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    let
      targetSystems = [ "x86_64-linux" "aarch64-linux" ];
    in flake-utils.lib.eachSystem targetSystems (system: let
      patches = with nixpkgs.legacyPackages.${system}; [
        ./patches/gaps.patch
        (fetchpatch {
          name = "fullscreen";
          url = "https://github.com/bakkeby/patches/blob/master/dwm/dwm-togglelayout-6.2.diff?raw=true";
          hash = "sha256-E6MNyhap5ceENYwIzp3bVYBrpDbVH9NMEteUDIOEGe4=";
        })
        ./patches/master-right.patch
        ./patches/rotatestack.patch
        ./patches/config.patch
      ];
      dwmOverlay = final: prev: {
        dwm = prev.dwm.overrideAttrs (_: {
          src = ./.;
          patches = patches;
        });
      };
      pkgs = import nixpkgs {
        inherit system;
        overlays = [ dwmOverlay ];
      };
    in rec {
      packages.default = pkgs.dwm;
      checks = packages;
      overlays = final: prev: {
        dwm = pkgs.dwm;
      };
    });
}
