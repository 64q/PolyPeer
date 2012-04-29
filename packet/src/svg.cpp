
    /**
	 * Création d'un paquet areYouReady
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_areYouReady ();
    
 	/**
	 * Création d'un paquet sendOperation
	 * @param string
	 *	adresse deuxieme PC client qui doit recevoir le chunk
	 * @param chunk
	 *	le contenu du fichier à faire passer
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_sendOperation (string secondDest, Chunk& chunk);

    /**
	 * Création d'un paquet sendChunk
	 * @param chunk
	 *	le contenu du fichier à envoyer
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_sendChunk (Chunk& chunk);

    /**
	 * Création d'un paquet readyToWork
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_readyToWork ();
    
    /**
	 * Création d'un paquet chunkReceived
	 * @param int
	 *	id du fichier qui a été recu
	 * @param int
	 *	chaunk du fichier recu
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_chunkReceived (int idFile, int numChunk);
    
   /**
	 * Création d'un paquet md5Error
	 * @param int
	 *	id du fichier qui a été recu
	 * @param int
	 *	chaunk du fichier recu
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_md5Error (int idFile, int numChunk);
