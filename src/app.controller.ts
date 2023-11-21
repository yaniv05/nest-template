import { Controller, Get } from '@nestjs/common';
import { ApiOperation, ApiResponse, ApiTags } from '@nestjs/swagger';
import { AppService } from './app.service';

@Controller()
@ApiTags('Test tags')
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  @ApiOperation({ summary: 'Renvoie Hello world !' })
  @ApiResponse({ description: 'description' })
  getHello(): string {
    return this.appService.getHello();
  }
}
