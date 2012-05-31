/*
 * Fichier spécial pour la consultation du log
 * Quentin Lebourgeois - 2012
 */
 
(function() {
	var args = pp.HashNav.vars;
	
	if (args.length < 2) {
		pp.Utils.error('404'); return;
	}
	
	pp.Ajax('/ajax/get_log', args[0] + '=' + args[1], function(content) {
		$('#log-content').text(content.content);
	});
})();
