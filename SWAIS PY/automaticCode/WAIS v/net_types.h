/* Net WAIS_v_7 - IOPT */
/* Automatic code generated by IOPT2C XSLT transformation. */


#ifndef __WAIS_v_7_DEFS
#define __WAIS_v_7_DEFS


#define TRACE_CONT_RUN       (-1)
#define TRACE_PAUSE          0
#define TRACE_SINGLE_STEP    1
#define TRACE_N_STEPS(n)     (n)

#define MODEL_NAME		WAIS_v_7
#define MODEL_NAME_STR		"WAIS_v_7"
#define MODEL_VERSION		"2019-03-12 15:38:17"
#define MODEL_N_INPUTS		2
#define MODEL_N_OUTPUTS		1
#define MODEL_N_PLACES		5
#define MODEL_N_TRANSITIONS	6

#ifdef __cplusplus
extern "C" {
#endif

extern int trace_control;

typedef struct {
    unsigned int p_4: 2; /* Place Verify Conditions to START */
    unsigned int p_5: 2; /* Place Rain Verified */
    unsigned int p_12: 2; /* Place Humidity Verified */
    unsigned int p_15: 2; /* Place Verify Conditions to STOP */
    unsigned int p_17: 2; /* Place Irrigation STOP */
    unsigned int padding: 6;
} WAIS_v_7_NetMarking;


typedef struct {
    unsigned int InS_Rain_Sensor : 7;
    unsigned int InS_Soil_Humidity_Sensor : 7;
} WAIS_v_7_InputSignals;


typedef struct {
} WAIS_v_7_InputSignalEvents;


typedef struct {
    unsigned int OE_Avtivate : 1;
    unsigned int OE_Desactivate : 1;
    unsigned int padding : 6;
} WAIS_v_7_OutputSignalEvents;


typedef struct {
} WAIS_v_7_PlaceOutputSignals;


typedef struct {
    unsigned int OuS_Valve : 1;
    unsigned int padding: 7;
} WAIS_v_7_EventOutputSignals;


typedef struct {
    unsigned int t_2 : 1; /* Start Irrigation */
    unsigned int t_3 : 1; /* Stop Irrigation */
    unsigned int t_6 : 1; /* Verify if rain < 30% */
    unsigned int t_7 : 1; /* Verify Soil Humidity < 30% */
    unsigned int t_19 : 1; /* Verify if Rain >= 30% */
    unsigned int t_20 : 1; /* Verify Soil Humidity >= 30% */
    unsigned int count: 8;
} WAIS_v_7_TransitionFiring;

/* Array declarations: */


/* Runtime text info: */
typedef struct {
#ifdef __cplusplus
    const
#endif
    char* name;
    int value;
} iopt_param_info;

extern iopt_param_info* get_WAIS_v_7_InputInfo();
extern iopt_param_info* get_WAIS_v_7_OutputInfo();
extern iopt_param_info* get_WAIS_v_7_MarkingInfo();
extern iopt_param_info* get_WAIS_v_7_TFiredInfo();
extern void force_WAIS_v_7_Inputs( iopt_param_info fv[], WAIS_v_7_InputSignals* in );
extern void force_WAIS_v_7_Outputs( iopt_param_info fv[], WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void force_WAIS_v_7_Marking( iopt_param_info fv[], WAIS_v_7_NetMarking* m );


extern void createInitial_WAIS_v_7_NetMarking( WAIS_v_7_NetMarking* init_marking );
extern void createEmpty_WAIS_v_7_NetMarking( WAIS_v_7_NetMarking* empty_marking );
extern void add_WAIS_v_7_NetMarkings( WAIS_v_7_NetMarking* dest_marking, WAIS_v_7_NetMarking* source_marking );

extern void init_WAIS_v_7_OutputSignals( WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );

/* Transition 2 - Start Irrigation */
extern int  t_2_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_2_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_2_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_2_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_2_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_2_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
/* Transition 3 - Stop Irrigation */
extern int  t_3_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_3_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_3_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_3_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_3_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_3_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
/* Transition 6 - Verify if rain < 30% */
extern int  t_6_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_6_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_6_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_6_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_6_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_6_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
/* Transition 7 - Verify Soil Humidity < 30% */
extern int  t_7_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_7_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_7_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_7_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_7_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_7_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
/* Transition 19 - Verify if Rain >= 30% */
extern int  t_19_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_19_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_19_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_19_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_19_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_19_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
/* Transition 20 - Verify Soil Humidity >= 30% */
extern int  t_20_enabled( WAIS_v_7_NetMarking* prev, WAIS_v_7_NetMarking* avail );
extern int  t_20_events( WAIS_v_7_InputSignalEvents* events );
extern int  t_20_guards( WAIS_v_7_NetMarking* marking, WAIS_v_7_InputSignals* inputs, WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* ev_out );
extern void t_20_remove_marks( WAIS_v_7_NetMarking* marking );
extern void t_20_add_marks( WAIS_v_7_NetMarking* marking );
extern void t_20_generate_output_events( WAIS_v_7_OutputSignalEvents* ev_out );
extern void WAIS_v_7_GenerateInputSignalEvents( WAIS_v_7_InputSignals *old_values, WAIS_v_7_InputSignals *new_values, WAIS_v_7_InputSignalEvents *events );

extern void WAIS_v_7_GenerateEventOutputSignals( WAIS_v_7_OutputSignalEvents *events, WAIS_v_7_EventOutputSignals *signals );

extern void WAIS_v_7_GenerateTransitionActionOutputSignals( WAIS_v_7_TransitionFiring *tfired, WAIS_v_7_NetMarking *marking, WAIS_v_7_EventOutputSignals *signals );

extern void WAIS_v_7_GeneratePlaceOutputSignals( WAIS_v_7_NetMarking *marking, WAIS_v_7_InputSignals *inputs, WAIS_v_7_PlaceOutputSignals *place_out, WAIS_v_7_EventOutputSignals *ev_out );

extern void WAIS_v_7_ExecutionStep( WAIS_v_7_NetMarking *prev_marking, WAIS_v_7_InputSignals *inputs, WAIS_v_7_InputSignals *prev_in, WAIS_v_7_PlaceOutputSignals *place_out, WAIS_v_7_EventOutputSignals *ev_out );

extern void WAIS_v_7_InitializeIO();
extern void WAIS_v_7_GetInputSignals( WAIS_v_7_InputSignals* inputs, WAIS_v_7_InputSignalEvents* events );
extern void WAIS_v_7_PutOutputSignals( WAIS_v_7_PlaceOutputSignals* place_out, WAIS_v_7_EventOutputSignals* event_out, WAIS_v_7_OutputSignalEvents* events );
extern void WAIS_v_7_LoopDelay();
extern int WAIS_v_7_FinishExecution( WAIS_v_7_NetMarking* marking );

extern WAIS_v_7_NetMarking* get_WAIS_v_7_NetMarking();
extern WAIS_v_7_InputSignals* get_WAIS_v_7_InputSignals();
extern WAIS_v_7_PlaceOutputSignals* get_WAIS_v_7_PlaceOutputSignals();
extern WAIS_v_7_EventOutputSignals* get_WAIS_v_7_EventOutputSignals();
extern WAIS_v_7_TransitionFiring* get_WAIS_v_7_TransitionFiring();

#ifdef __cplusplus
};
#endif


#endif
