{ pkgs }: {
    deps = [
		pkgs.sudo
  		pkgs.run
  		pkgs.nodePackages.prettier
        pkgs.cowsay
		pkgs.gcc
		pkgs.ncurses
	];
} 
