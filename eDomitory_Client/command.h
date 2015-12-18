/*
 * This proxy is not a secure proxy.
 * Please DO NOT USE IT in important cases!
 */
 
struct command
{
  short commandHeader[2];
  long commandData[10];
};

int commandToVar(struct command cmd,int dataType,int *action,int *data)
{
  int i;
  if (cmd.commandHeader[0]!=0xdc)
  {
    return 0;
  }
  if (cmd.commandHeader[1]!=cmd.commandData[0]&0x03)
  {
    return 0;
  }
  if (cmd.commandData[1]&0x01!=dataType)
  {
    return 0;
  }
  *action=cmd.commandData[1];
  if (*action&0x01)
    *data=cmd.commandData[2];
  else
    for (i=0;i<9;++i)
      data[i]=cmd.commandData[i+1];
  return 1;
}

int varToCommand(int action,int data,struct command *cmd)
{
  cmd->commandHeader[0]=0xdc; //Mark for Domitory Connection
  cmd->commandHeader[1]=action&0x03;
  cmd->commandData[1]=action;
  cmd->commandData[2]=data;
  return 1;
}

