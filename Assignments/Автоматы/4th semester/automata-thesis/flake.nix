{
  description = "Typst flake";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs:
    inputs.flake-parts.lib.mkFlake {inherit inputs;} {
      systems = ["x86_64-linux"];
      perSystem = {pkgs, ...}: let
        alias = pkgs.writeShellScriptBin;
        aliases = [
          (alias "workflow" ''
            mkdir -p ./target
            typst watch ./src/main.typ ./target/main.pdf &
            zathura ./target/main.pdf &
          '')
        ];
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs;
            [
              typst
            ]
            ++ aliases;
        };
      };
    };
}
