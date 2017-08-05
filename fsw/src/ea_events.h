    
#ifndef EA_EVENTS_H
#define EA_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/


/* Event IDs
 * Conventions: _EID is the event identifier.  _EVT_CNT is the total number of
 * events and should always be last.  Events can be added before _EVT_CNT.
 * For long-term maintenance, consider not removing an event but replacing it
 * with an unused, reserved, enum to preserve the IDs later in the list. */
typedef enum {

/** \brief <tt> Value of zero is reserved, and should not be used. </tt> */
    EA_RESERVED_EID = 0,  /* Do not use this event ID */

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  TODO fill this in
**
*/
    EA_INF_EID,

/** \brief <tt> 'EA Initialized. Version \%d.\%d.\%d' </tt>
**  \event <tt> 'EA Initialized. Version \%d.\%d.\%d' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  completed initialization.
**
**  The first \c %d field contains the Application's Major Version Number
**  The second \c %d field contains the Application's Minor Version Number
**  The third \c %d field contains the Application's Revision Number
*/
    EA_INIT_INF_EID,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This message is generated when a table is initialized.
**
*/
    EA_CONFIG_TABLE_INF_EID,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    EA_CDS_INF_EID,

/** \brief <tt> 'EA - Recvd $x cmd (%us)' </tt>
**  \event <tt> 'EA - Recvd $x cmd (%us)' </tt>
**  
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received and processed a command.
**
*/
    EA_CMD_INF_EID,

/** \brief <tt> 'EA - Recvd $x cmd (%us)' </tt> TODO
**  \event <tt> 'EA - Recvd $x cmd (%us)' </tt>
**
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received and processed a command.
**
*/
	EA_INF_APP_START,

/** \brief <tt> 'EA - Recvd $x cmd (%us)' </tt> TODO
**  \event <tt> 'EA - Recvd $x cmd (%us)' </tt>
**
**  \par Type: INFORMATION
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received and processed a command.
**
*/
	EA_INF_APP_TERM,

/** \brief <tt> 'EA - Recvd $x cmd (%us)' </tt> TODO
**  \event <tt> 'EA - Recvd $x cmd (%us)' </tt>
**
**  \par Type: WARNING TODO?
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received and processed a command.
**
*/
	EA_WARN_APP_UTIL,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when TBD
**
*/
    EA_ERR_EID,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  had an error in initialization.
**
*/
    EA_INIT_ERR_EID,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  had an error with the configuration table.
**
*/
    EA_CONFIG_TABLE_ERR_EID,

/** \brief <tt> 'EA - ' </tt>
**  \event <tt> 'EA - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  had an error in CDS.
**
*/
    EA_CDS_ERR_EID,

/** \brief <tt> 'EA - $commandError' </tt>
**  \event <tt> 'EA - $commandError' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  had an error processing a command.
**
*/
    EA_CMD_ERR_EID,

/** \brief <tt> 'EA: SB pipe read error (0x%08X), app will exit' </tt>
**  \event <tt> 'EA: SB pipe read error (0x%08X), app will exit' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  had an error reading from a pipe.
**
*/
    EA_PIPE_ERR_EID,

/** \brief <tt> 'EA - Recvd invalid $type msgId (0x%04x)' </tt>
**  \event <tt> 'EA - Recvd invalid $type msgId (0x%04x)' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received an invalid message ID.
**
*/
    EA_MSGID_ERR_EID,

/** \brief <tt> 'EA - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  \event <tt> 'EA - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, msgLen=%d, expectedLen=%d" </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when the CFS EA Task has
**  received a message with a bad length.
**
*/
    EA_MSGLEN_ERR_EID,


/** \brief <tt> This is a count of all the app events and should not be used. </tt> */
    EA_EVT_CNT
} EA_EventIds_t;


#ifdef __cplusplus
}
#endif

#endif /* EA_EVENTS_H */

/************************/
/*  End of File Comment */
/************************/
    
