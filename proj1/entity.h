#define		MAX_ENTITY_TEXT_LENGTH				256

typedef struct {

	BYTE					EntityType; //1 action 2 class	3 condation 4 Individual 5 Property 6 QTool 7 Advervb 8 Property+Verb
	char					Entity[MAX_ENTITY_TEXT_LENGTH];
	char					StemmedEntity[MAX_ENTITY_TEXT_LENGTH];
	int						ParentEntityId;
	int						EntityId;
	int						SenseId;

	BYTE					Language;	//0 Arabic 1 English
	BYTE					*ParentEntity = NULL;
	int						ParentIndex;
	int						classId;
	int						PropertyId;
	bool					ambClass;
	bool					Required;
	bool					GenRelEntity;

	int						Frequency;

	CIntList				*StemsList;

	bool					Gen = false;
	BYTE					Gender = 0;//0: no type, 1: male, 2: female
	BYTE					Type = 0 ;//1- time 2-Place 3-Count

	CIntList				*IndividualsList = NULL;

	FRAME_LIST				*FirstSbjFrame = NULL;
	FRAME_LIST				*LastSbjFrame = NULL;

	FRAME_LIST				*FirstObjFrame = NULL;
	FRAME_LIST				*LastObjFrame = NULL;

	FRAME_LIST				*FirstComplementFrame = NULL;
	FRAME_LIST				*LastComplementFrame = NULL;

	//FRAME_LIST				*FirstPropFrame = NULL;
	//FRAME_LIST				*LastPropFrame = NULL;

	FRAME_LIST				*FirstLinkedPropFrame = NULL;
	FRAME_LIST				*LastLinkedPropFrame = NULL;

	FACT_PROPERTY_LIST_T	*FirstFact = NULL;
	FACT_PROPERTY_LIST_T	*LastFact = NULL;

	FACT_PROPERTY_LIST_T	*FirstClassProperty = NULL;
	FACT_PROPERTY_LIST_T	*LastClassProperty = NULL;


	int						ParentClassFactIndex = -1;
	int						LastPropertyIndex = -1;
}LOOKUP_ENTITIES_STR;