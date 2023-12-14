import {
    Body,
    Controller,
    Delete,
    Get,
    Param,
    Post,
    Request
  } from '@nestjs/common'
import { ApiBearerAuth, ApiBody, ApiOperation, ApiTags } from '@nestjs/swagger'
import { UserService } from './user.service'
import {CreateUserDto} from './dto/create-user.dto'

@Controller('user')
@ApiTags('User')
export class UserController {
    constructor (private readonly userService: UserService) {}

    @Get('/all')
    @ApiOperation({ summary: 'Get all users' })
    async index () {
      return await this.userService.findAll()
    }

    @Post('register')
    register(
      @Body() createUserDto: CreateUserDto,
    ): Promise<any> {
      return this.userService.create(createUserDto);
    }
}
