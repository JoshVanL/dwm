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
        #(fetchpatch {
        #  name = "gaps";
        #})
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
    in {
      packages = {
        default = pkgs.dwm;
      };
    });
}
