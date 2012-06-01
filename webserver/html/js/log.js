/*
 * Fichier spécial pour la consultation du log
 * Quentin Lebourgeois - 2012
 */
 
(function() {
	var args = pp.HashNav.vars;
	
	if (args.length < 1) {
		pp.Utils.error('404'); return;
	}
	
	pp.Ajax('/ajax/get_log', 'log=' + args[0], function(content) {
		if (content == "error") {
			notifyError('Impossible de récupérer le fichier de log !');
		} else {
			$('#log-content').text(content);
			$('#log-header').text(args[0]);
			window.scrollTo(0, window.innerHeight); // Scroll en bas
		}
	}, function(){}, false);
})();
