/*
 * This proxy is not a secure proxy.
 * Please DO NOT USE IT in important cases!
 */

#define DATA_COUNT 5

struct command
{
  short commandHeader[2];
  long commandData[DATA_COUNT];
};

int commandToVar(struct command cmd,int dataType,long *action,long *data) //Convert package to variables
{
  int i;
  if (cmd.commandHeader[0]!=0xdc)
  {
    return 2;
  }
  if (cmd.commandHeader[1]!=cmd.commandData[0]&0x03)
  {
    return 3;
  }
  if (cmd.commandData[0]&0x01!=dataType)
  {
    return 4;
  }
  *action=cmd.commandData[0];
  if (*action&0x01)
    *data=cmd.commandData[1];
  else
    for (i=0;i<DATA_COUNT-1;++i)
      data[i]=cmd.commandData[i+1];
  return 1;
}

int varToCommand(int action,const long *data,struct command *cmd) //Convert variables to package
{
  int i;
  
  cmd->commandHeader[0]=0xdc; //Mark for Domitory Connection
  cmd->commandHeader[1]=action&0x03;
  cmd->commandData[0]=action;
  if (action&0x01)
    cmd->commandData[1]=*data;
  else
    for (i=0;i<DATA_COUNT-1;++i)
      cmd->commandData[i+1]=data[i];
  return 1;
}

