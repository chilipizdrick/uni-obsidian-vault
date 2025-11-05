{
  description = "SUBD flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs: let
    system = "x86_64-linux";
    pkgs = import inputs.nixpkgs {
      inherit system;
      config.allowUnfree = true;
    };
  in {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        vscode
        python3
        python3Packages.pip
        python3Packages.matplotlib
        python3Packages.pandas
        python3Packages.notebook
        python3Packages.jupysql
        python3Packages.jupyterlab-lsp
      ];
    };
  };
}
